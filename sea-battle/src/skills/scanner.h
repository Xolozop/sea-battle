#ifndef SCANNER_H
#define SCANNER_H

#include "skill.h"

class Scanner : public Skill {
private:
    skillIDs id = skillIDs::scanner;
public:
    bool useSkill(Field& field, shipManager& manager, bool& DAFlag, char y, int x) override;
    std::string getName() const override;
    skillIDs getId() override;
};

#endif