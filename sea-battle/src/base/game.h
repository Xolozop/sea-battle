#ifndef GAME_H
#define GAME_H

#include <ctime>

#include "../skills/skill.h"
#include "exceptions.h"
#include "gameState.h"

#define SHIP_CNT 10
#define MAX_SHIP_LEN 4

typedef struct coord_t {
    char ver;
    int hor;
} coord_t;

enum atackResults {missed, segDamaged, segDestroyed, shipDestroyed};
enum skillResults {isShip, noShip, success};

class Game {
public:
    gameState state;
    skillManager& playerSkills = state.playerSkills;
    shipManager& playersManager = state.playersManager;
    shipManager& enemyManager = state.enemyManager;
    Field& playerField = state.playerField;
    Field& enemyField = state.enemyField;
    bool doubleAtackFlag = false;

    Game& operator=(const Game& other);

    bool checkSave();

    void initializeEnemyField();

    int setAtack(coord_t coords);
    atackResults useAtack(coord_t coords, int tmp);
    skillResults useSkill(coord_t coords);

    void enemyTurn();

    void clearRound(bool clearPlayer);
};

#endif