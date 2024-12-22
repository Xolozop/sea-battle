#ifndef GAME_STATE_H
#define GAME_STATE_H

#include "ship.h"
#include "field.h"
#include "shipManager.h"
#include "../skills/skillManager.h"
#include "file.h"

#define FIELD_SZ 10

typedef struct score_t {
    int player;
    int enemy;
} score_t;

class gameState {
public:
    score_t score = {0, 0}; 
    skillManager playerSkills = skillManager();
    shipManager playersManager = shipManager(0, std::vector<std::vector<Ship>>(0));
    shipManager enemyManager = shipManager(0, std::vector<std::vector<Ship>>(0));
    Field playerField = Field(FIELD_SZ, true);
    Field enemyField = Field(FIELD_SZ, false);

    friend std::istream& operator>>(std::istream& is, gameState& gameState);
    friend std::ostream& operator<<(std::ostream& os, const gameState& gameState);

    // Сохранение состояния игры
    void save();
    // Загрузка состояния игры
    void load();
};

#endif