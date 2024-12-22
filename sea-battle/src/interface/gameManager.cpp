#include "gameManager.h"

template <class T, class D1, class D2>
gameManager<T, D1, D2>::gameManager(Game& g, Printer<D1, D2> p, T h) : game{g}, printer{p}, handler{h}{ }

template <class T, class D1, class D2>
void gameManager<T, D1, D2>::run() {
    bool def = true;
    if (game.checkSave()) {
        printer.printLog("The save is available and will be load.", logTypes::mes);
        bool agred = false;
        bool ans;
        while (!agred) {
            try {
                ans = handler.getAgreement();
                agred = true;
            } catch (const improperInputException& e) {
                printer.printLog(e.what(), logTypes::error);
            }
        }
        if (ans) {
            try {
                Game nw;
                nw.state.load();
                game = nw;
                def = true;
                printer.printLog("Game state succesfully restored.", logTypes::hooray);
            } catch (const std::exception& e) {
                printer.printLog(e.what(), logTypes::error);
            }
        }
    }

    if (def) {
        setShips();
        game.initializeEnemyField();
    }

    bool gameInProc = true;
    while (gameInProc) {
        printer.drawField(game);

        commands command;
        bool valid = false;
        while (!valid) {
            try {
                command = handler.getCommand();
                valid = true;
            } catch (const std::exception& e) {
                printer.printLog(e.what(), logTypes::error);
            }
        }

        bool validInput = false;
        switch (command) {
            case commands::atack:
                while (!validInput) {
                    try {
                        coord_t coords = handler.getCoords();
                        game.enemyField.validateCoords(coords.ver, coords.hor);
                        int tmp = game.setAtack(coords);
                        printer.drawField(game);
                        bool agreed = handler.getAgreement();
                        if (!agreed)
                            continue;
                        atackResults res = game.useAtack(coords, tmp);
                        std::string skill = "";
                        try {
                            skill = game.playerSkills.getLastName();
                        } catch(...) { }
                        printer.printAtackRes(res, skill);
                        validInput = true;
                    } catch (const std::exception& e) {
                        printer.printLog(e.what(), logTypes::error);
                        continue;
                    }
                }
                break;
            case commands::skill:
                while (!validInput) {
                    try {
                        coord_t coords = {0, 0};
                        if (game.playerSkills.getLastID() == skillIDs::scanner) {
                            coords = handler.getCoords();
                            game.enemyField.validateCoords(coords.ver, coords.hor);
                        }
                        game.useSkill(coords);
                        validInput = true;
                    } catch (const std::exception& e) {
                        printer.printLog(e.what(), logTypes::error);
                        continue;
                    }
                }
                break;
            case commands::save:
                try {
                    game.state.save();
                    printer.printLog("Succesfully saved!", logTypes::hooray);
                    validInput = true;
                } catch (const std::exception& e) {
                    printer.printLog(e.what(), logTypes::error);
                    continue;
                }
                continue;
            case commands::quit:
                printer.printLog("You changes willl not be saved. Do you want to save it?", logTypes::mes);
                if (handler.getAgreement()) {
                    try {
                        game.state.save();
                        printer.printLog("Succesfully saved!", logTypes::hooray);
                        validInput = true;
                    } catch (const std::exception& e) {
                        printer.printLog(e.what(), logTypes::error);
                        continue;
                    }
                }
                gameInProc = false;
                break;
        }

        if (!gameInProc)
            break;

        game.enemyTurn();
        printer.drawField(game);

        if (game.enemyManager.isAllShipsDestroyed()) {
            game.state.score.player++;
            printer.printLog("YOU'RE WIN!!!", logTypes::hooray);
            printer.printLog("Starting new game...", logTypes::mes);
            game.clearRound(false);
        }

        if (game.playersManager.isAllShipsDestroyed()) {
            game.state.score.enemy++;
            printer.printLog("You are lose......", logTypes::bad);
            printer.printLog("Starting new game...", logTypes::mes);
            game.clearRound(true);
            setShips();
        }
    }
}

template <class T, class D1, class D2>
void gameManager<T, D1, D2>::setShips() {
    int k = 0;
    while (!game.playersManager.isAllShipsEntered()) {
        printer.drawField(game, true);
        bool valid = false;
        int len;
        while (!valid) {
            try {
                len = handler.getLen();
                valid = true;
            } catch (const std::exception& e) {
                printer.printLog(e.what(), logTypes::error);
            }
        }
        valid = false;
        char ori;
        while (!valid) {
            try {
                ori = 'v';
                if (len > 1)
                    ori = handler.getOri();
                valid = true;
            } catch(const std::exception& e) {
                printer.printLog(e.what(), logTypes::error);
            }
        }

        Ship tmp(len, ori);
        try {
            game.playersManager.refresh(tmp);
        } catch (const shipListIsFullException& e) {
            printer.printLog(e.what(), logTypes::error);
            continue;
        }

        coord_t shipCoords;
        bool isShipPlaced = false;
        while (!isShipPlaced) {
            try {
                shipCoords = handler.getCoords();
                game.enemyField.validateCoords(shipCoords.ver, shipCoords.hor);
                game.playerField.setShip(tmp, shipCoords.ver, shipCoords.hor, game.playersManager.getShipIndex(tmp.getLength()));
            } catch (const std::exception& e) {
                printer.printLog(e.what(), logTypes::error);
                continue;
            }

            printer.drawField(game);
            bool agreed = false;
            while (!agreed) {
                try {
                    bool ans = handler.getAgreement();
                    if (!ans)
                        game.playerField.deletePrevShip();
                    agreed = true;
                } catch (const std::exception& e) {
                    printer.printLog(e.what(), logTypes::error);
                }
            }
            isShipPlaced = true;
        }
    }
}

template class gameManager<inputHandler, termDrawer, termLogger>;