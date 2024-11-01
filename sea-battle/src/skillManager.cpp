#include <iostream>
#include <ctime>

#include "field.h"
#include "skillManager.h"
#include "exceptions.h"
#include "skill.h"
#include "doubleAtack.h"
#include "scanner.h"
#include "shelling.h"

skillManager::skillManager(Field& field, shipManager& manager) {
    srand(time(0));
    skills.resize(3);
    int i = std::rand()%3;
    int j = std::rand()%3;
    while (j == i)
        j = (j+1)%3;
    int k = 3 - i - j;
    // generate 3 random numbers from 0 to 2
    skills[i] = new doubleAtack(field, manager);
    skills[j] = new Scanner(field, manager);
    skills[k] = new Shelling(field, manager);
}

skillManager::~skillManager() {
    for (int i = 0; i < skills.size(); i++)
        delete skills[i];
}

void skillManager::addRandomSkill(Field& field, shipManager& manager) {
    int x = std::rand()%3;
    Skill* tmp;
    switch(x) {
        case 0:
            tmp = new doubleAtack(field, manager);
            break;
        case 1:
            tmp = new Shelling(field, manager);
            break;
        default:
            tmp = new Scanner(field, manager);
    }
    skills.push_back(tmp);
}


void skillManager::useLastSkill() {
    if (skills.size() == 0)
        throw noSkillsException();
    skills[skills.size()-1]->useSkill();
    delete skills[skills.size()-1];
    skills.pop_back();
}