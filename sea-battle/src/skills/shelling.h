#ifndef SHELLING_H
#define SHELLING_H

#include "skill.h"
class Shelling : public Skill {
private:
    skillIDs id = skillIDs::shelling;
public:
    bool useSkill(Field& field, shipManager& manager, bool& DAFlag, char y, int x) override;
    std::string getName() const override;
    skillIDs getId() override;
};

#endif