#ifndef SKILL_MANAGER_H
#define SKILL_MANAGER_H

#include "skill.h"
#include "field.h"
#include "shipManager.h"

class skillManager 
{
private:
    std::vector<Skill*> skills;
public:
    skillManager(Field& field, shipManager& manager);
    ~skillManager();
    void addSkill(Skill skill);
    void addRandomSkill(Field& field, shipManager& manager);
    void useLastSkill();
};

#endif