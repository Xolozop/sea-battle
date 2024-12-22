#ifndef DOUBLE_ATACK_H
#define DOUBLE_ATACK_H

#include "skill.h"

class doubleAtack : public Skill {
private:
    skillIDs id = skillIDs::doubleAtack;
public:
    bool useSkill(Field& field, shipManager& manager, bool& DAFlag, char y, int x) override;
    std::string getName() const override;
    skillIDs getId() override;
};

#endif