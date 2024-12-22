#include "game.h"

Game& Game::operator=(const Game& other) {
    if (this != &other) {
        state = other.state;
        playerSkills = other.playerSkills;
        playersManager = other.playersManager;
        enemyManager = other.enemyManager;
        playerField = other.playerField;
        enemyField = other.enemyField;
        doubleAtackFlag = other.doubleAtackFlag;
    }
    return *this;
}

bool Game::checkSave() {
    try {
        File file("save.txt", true);
        return true;
    } catch (const fileWriteException& e) {
        return false;
    }
}

void Game::initializeEnemyField() {
    int x, y;
    for (int len = 0; len < MAX_SHIP_LEN; len++) {
        for (int count = 0; count < (MAX_SHIP_LEN - len); count++) {
            char ori = std::rand()%2 ? 'v' : 'h'; 
            Ship tmp(len+1, ori);
            enemyManager.refresh(tmp);
            bool shipIsPlaced = false;
            while (!shipIsPlaced) {
                y = std::rand()%FIELD_SZ;
                x = std::rand()%FIELD_SZ;
                try {
                    enemyField.setShip(tmp, (char)(y + 97), x, count+1);
                    shipIsPlaced = true;
                } catch (const std::exception& myExc) {
                    enemyField.deletePrevShip();
                }
            }
        }
    }
}

int Game::setAtack(coord_t coords) {
    return enemyField.setGunpoint(coords.ver, coords.hor, enemyManager);
}

atackResults Game::useAtack(coord_t coords, int tmp_val) {
    enemyField.shoot(coords.ver, coords.hor, enemyManager, doubleAtackFlag, tmp_val);

    int tmp_ship = enemyField.isShip(coords.ver, coords.hor);
    if (tmp_ship) {
        Ship ship = enemyManager.getShip(tmp_ship/100, (tmp_ship%100)/10);
        segStates res = ship.getState(tmp_ship%10);
        if (res == segStates::damaged)
            return atackResults::segDamaged;
        else
            return atackResults::segDestroyed;

        if (ship.isShipDestroyed()) {
            playerSkills.addRandomSkill();
            return atackResults::shipDestroyed;
        }
    }
    return atackResults::missed;
}

skillResults Game::useSkill(coord_t coords) {
    bool res = playerSkills.useLastSkill(enemyField, enemyManager, doubleAtackFlag, coords.hor, coords.ver);
    if (playerSkills.getLastID() == skillIDs::scanner)
        return res ? skillResults::isShip : skillResults::noShip;
    else
        return skillResults::success;
}

void Game::enemyTurn() {
    bool shoted = false;
    while (!shoted) {
        int y = std::rand()%FIELD_SZ;
        int x = std::rand()%FIELD_SZ;
        try {
            playerField.validateCoords((char)(y + 97), x);
            bool tmp = false;
            playerField.shoot((char)(y + 97), x+1, playersManager, tmp, 0);
            shoted = true;
        } catch (const std::exception& myExc) { }
    }
}

void Game::clearRound(bool clearPlayer=false) {
    enemyManager = shipManager(0, std::vector<std::vector<Ship>>(0));
    enemyField = Field(FIELD_SZ, false);
    initializeEnemyField();
    if (clearPlayer) {
        playerSkills = skillManager();
        playersManager = shipManager(0, std::vector<std::vector<Ship>>(0));
        playerField = Field(FIELD_SZ, true);
    }
}