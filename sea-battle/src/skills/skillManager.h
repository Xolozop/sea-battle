#ifndef SKILL_MANAGER_H
#define SKILL_MANAGER_H

#include "skill.h"

class skillManager 
{
private:
    std::vector<Skill*> skills;
    std::vector<Skill*> uniqueSkills;
public:
    skillManager();
    skillManager(std::vector<int> ids);
    ~skillManager();
    void makePool();
    void addRandomSkill();
    skillIDs getLastID();
    std::string getLastName();
    bool useLastSkill(Field& field, shipManager& manager, bool& DAFlag, char y, int x);
    std::string getSkillList() const;
    std::string saveSkills() const;
};

#endif