#include <iostream>
#include <climits>
#include <ctime>

#include "exceptions.h"
#include "ship.h"
#include "shipManager.h"
#include "field.h"
#include "skillManager.h"
#include "skill.h"
#include "doubleAtack.h"
#include "scanner.h"
#include "shelling.h"

#define FIELD_SZ 10
#define TERM_GREEN "\033[32m"
#define TERM_RED "\033[31m"
#define TERM_DEF "\033[0m"
// works only on linux

shipManager createEnemyField(Field* enemyField) {
    std::vector<std::vector<Ship>> enemyShips(4);
    shipManager manager = shipManager(0, enemyShips);
    int x, y;
    int amount = 0;
    for (int len = 0; len < enemyShips.size(); len++) {
        for (int count = 0; count < (4 - len); count++) {
            char ori = (len%2) ? 'h' : 'v'; 
            Ship tmp(len+1, ori);
            enemyShips[len].push_back(tmp);
            //srand(time(0));
            while (1) {
                y = std::rand()/(RAND_MAX/FIELD_SZ);
                x = std::rand()/(RAND_MAX/FIELD_SZ);
                try {
                    enemyField->setShip(tmp, (char)(y + 97), x, count+1);
                } catch (const std::exception& myExc) {
                    continue;
                }
                break;
            }
            amount++;
        }
    }
    manager = shipManager(amount, enemyShips);

    return manager;
}

int main() {
    Field enemyField(FIELD_SZ, false);
    // change to true to see field and skipi confirmation
    shipManager enemyManager = createEnemyField(&enemyField);
    
    Field playersField(FIELD_SZ, true);
    std::vector<std::vector<Ship>> playersShips;
    shipManager playersManager(0, playersShips);
    skillManager playersSkills(enemyField, enemyManager);

    int shipAmount = 0;

    int len = 4;
    Ship ship1(len, 'v');
    playersManager.refresh(ship1);
    shipAmount++;

    try {
        Ship shipErr(5, 'h');
        playersManager.refresh(shipErr);
        shipAmount++;
    } catch (const std::exception& myExc) {
        std::cerr << TERM_RED << myExc.what() << TERM_DEF << std::endl;  // Improper length of ship
    }
    try {
        Ship shipErr(0, 'h');
        playersManager.refresh(shipErr);
        shipAmount++;
    } catch (const std::exception& myExc) {
        std::cerr << TERM_RED << myExc.what() << TERM_DEF << std::endl;  // Improper length of ship
    }
    try {
        Ship shipErr(2, 's');
        playersManager.refresh(shipErr); // Improper orientation
        shipAmount++;
    } catch (const std::exception& myExc) {
        std::cerr << TERM_RED << myExc.what() << TERM_DEF << std::endl;
    }
    try {
        Ship shipErr(len, 'h');
        playersManager.refresh(shipErr);  // All ships of this length are already in the list
        shipAmount++;
    } catch (const std::exception& myExc) {
        std::cerr << TERM_RED << myExc.what() << TERM_DEF << std::endl;
    }

    len = 2;
    Ship ship2(len, 'h');
    playersManager.refresh(ship2);
    shipAmount++;

    try { 
        playersField.setShip(ship1, 'c', 8, playersManager.getShipIndex(len)); 
    } catch (const std::exception& myExc) { 
        std::cerr << TERM_RED << myExc.what() << TERM_DEF << std::endl; // Coordinations out of field
    }
    playersField.setShip(ship1, 'c', 3, playersManager.getShipIndex(len));
    
    try {
        playersField.setShip(ship2, 'd', 6, playersManager.getShipIndex(len)); // You can't put a ship right next to another one
    } catch (const std::exception& myExc) {
        std::cerr << TERM_RED << myExc.what() << TERM_DEF << std::endl;
    }
    try { 
        playersField.setShip(ship2, 'j', 10, playersManager.getShipIndex(len)); // Coordinates out of field! 
    } catch (const std::exception& myExc) { 
        std::cerr << TERM_RED << myExc.what() << TERM_DEF << std::endl; 
    }
    try {
        playersField.setShip(ship2, 'c', 6, playersManager.getShipIndex(len));  // There's already a ship here! 
    } catch (const std::exception& myExc) {
        std::cerr << TERM_RED << myExc.what() << TERM_DEF << std::endl;
    }
    playersField.setShip(ship2, 'i', 10, playersManager.getShipIndex(len));

    // enemyField.shoot('g', 5, enemyManager);
    // enemyField.shoot('e', 5, enemyManager);
    
    try {
        enemyField.shoot('k', 5, enemyManager);
    } catch(const std::exception& myExc) {
        std::cerr << TERM_RED << myExc.what() << TERM_DEF << std::endl; // Coordinates out of field
    }
    try {
        enemyField.shoot('a', 11, enemyManager);
    } catch(const std::exception& myExc) {
        std::cerr << TERM_RED << myExc.what() << TERM_DEF << std::endl; // Coordinates out of field
    }
    try {
        enemyField.shoot('i', 3, enemyManager);
        enemyField.shoot('i', 3, enemyManager);
        int tmp = enemyField.isShip('i'-96-1, 3-1);
        if (tmp && enemyManager.getShip(tmp/100, (tmp%100)/10).isShipDestroyed()) {
            std::cout << TERM_GREEN << "\tShip destroyed!!!" << std::endl;
            std::cout << "You recieve one special skill!" << TERM_DEF << std::endl;
            playersSkills.addRandomSkill(enemyField, enemyManager);
        }
    } catch(const std::exception& myExc) {
        std::cerr << TERM_RED << myExc.what() << TERM_DEF << std::endl; // You already destroyed the ship segment at these coordinates! 
    }

    while(1) {
        try {
            playersSkills.useLastSkill();
        } catch(const noSkillsException& myExc) {
            std::cerr << TERM_RED << myExc.what() << TERM_DEF << std::endl; // No skills left!
            break;
        }
    }
    
    std::cout << "Your ships: " << std::endl;
    playersManager.printShipList();
    std::cout << "Your field: " << std::endl;
    playersField.printField(true, playersManager);
    std::cout << std::endl;
    std::cout << "Enemy ships: " << std::endl;
    enemyManager.printShipList();
    std::cout << "Enemy field: " << std::endl;
    enemyField.printField(false, enemyManager);
    return 0;
}