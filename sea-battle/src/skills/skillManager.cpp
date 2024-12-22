#include <iostream>
#include <random>

#include "../base/exceptions.h"
#include "skillManager.h"
#include "skill.h"
#include "doubleAtack.h"
#include "scanner.h"
#include "shelling.h"

skillManager::skillManager() {
    makePool();
    skills = uniqueSkills;
    std::random_device rd;
    std::mt19937 g(rd());
    std::shuffle(skills.begin(), skills.end(), g);
    uniqueSkills.clear();
}

skillManager::skillManager(std::vector<int> ids) {
    for (int id : ids) {
        makePool();
        if (id < 0 || id > 2)
            throw fileReadException();
        skills.push_back(std::move(uniqueSkills[id]));
        uniqueSkills.clear();
    }
}

skillManager::~skillManager() {
    skills.clear();
}

void skillManager::makePool() {
    uniqueSkills.push_back(new class doubleAtack());
    uniqueSkills.push_back(new class Scanner());
    uniqueSkills.push_back(new class Shelling());
}

void skillManager::addRandomSkill() {
    makePool();
    srand(time(0));
    int x = std::rand()%3;
    skills.push_back(std::move(uniqueSkills[x])); 
    std::cout << "Your new skill: " << skills.back()->getName() << std::endl;
    uniqueSkills.clear();
}

skillIDs skillManager::getLastID() {
    if (skills.empty())
        throw noSkillsException();
    return skills.front()->getId();
}

std::string skillManager::getLastName() {
    if (skills.empty())
        throw noSkillsException();
    return skills.front()->getName();
}

bool skillManager::useLastSkill(Field& field, shipManager& manager, bool& DAFlag, char y, int x) {
    if (skills.empty())
        throw noSkillsException();
    Skill* skill = skills.front();
    std::cout << "Using " << skill->getName() << "..." << std::endl;
    bool res = skill->useSkill(field, manager, DAFlag, x, y);
    skillIDs id = skill->getId();
    delete skills[0];
    skills.erase(skills.begin());

    return res;
}

std::string skillManager::getSkillList() const {
    std::string res;
    if (skills.empty())
        return "None";
    for (auto skill : skills) {
        res += skill->getName() + "  ";
    }
    return res;
}

std::string skillManager::saveSkills() const {
    std::stringstream res;
    if (skills.empty())
        return "-1";
    for (auto skill : skills) {
        res << skill->getId() << " ";
    }
    return res.str();
}