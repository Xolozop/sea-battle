#include <iostream>
#include <iomanip> // for setw
#include <ctime> // for srand(time)

#include "shipManager.h"
#include "exceptions.h"

#define MAX_SHIP_COUNT 10
#define TERM_UNDERLINE "\033[4m"
#define TERM_DEF "\033[0m"

shipManager::shipManager(int am, std::vector<std::vector<Ship>> shipArray) : amount{am} {
    ships.resize(shipArray.size());
    for (int x = 0; x < shipArray.size(); x++) {
        for (int y = 0; y < shipArray[x].size(); y++) {
            ships[x].push_back(shipArray[x][y]);
        }
    }
}

void shipManager::refresh(Ship ship) {
    int len = ship.getLength();
    if (ships.size() < len)
        ships.resize(len);
    if (ships[len-1].size() >= (5 - len))
        throw shipListIsFullException();
    ships[len-1].push_back(ship);
    amount++;
}

bool shipManager::isAllShipsEntered() const {
    return (amount == MAX_SHIP_COUNT);
}

int shipManager::getShipIndex(int len) const {
    return ships[len-1].size();
}

Ship& shipManager::getShip(int x, int y) {
    return ships[x-1][y-1];
}

void shipManager::printShipList() const {
    std::cout << TERM_UNDERLINE << "\t  №  |";
    for (int i = 1; i < amount+1; i++)
            std::cout << "  " << i << "  |";

    std::cout << TERM_DEF << std::endl;
    std::cout << "\tShip |";
    for (int x = 0; x < ships.size(); x++) {
        for (int y = 0; y < ships[x].size(); y++) {
            std::cout << std::setw(2-x/2) << ' ';
            for (int i = 1; i <= x+1; i++)
                ships[x][y].printSeg(i);
            std::cout << std::setw(2-(x+1)/2) << ' ';
            std::cout << "|";
        }
    }
    std::cout << std::endl;
}

bool shipManager::isAllShipsDestroyed() const {
    for (int x = 0; x < ships.size(); x++) {
        for (int y = 0; y < ships[x].size(); y++) {
            if (!ships[x][y].isShipDestroyed())
                return false;
        }
    }
    return true;
}

int* shipManager::getRandomUndamagedShip() const {
    srand(time(0));
    std::vector<int*> intactShips;
    for (int x = 0; x < ships.size(); x++) {
        for (int y = 0; y < ships[x].size(); y++) {
            if (ships[x][y].hasIntactSegs()) {
                int* tmp = new int[2];
                tmp[0] = x;
                tmp[1] = y;
                intactShips.push_back(tmp);
            }
        }
    }

    if (intactShips.size() == 0)
        throw shellingException();

    int i = std::rand()%intactShips.size();
    int* ret = intactShips[i];
    for (int j = 0; j < intactShips.size(); j++) {
        if (j != i)
            delete intactShips[j];
    }
    return ret;
}