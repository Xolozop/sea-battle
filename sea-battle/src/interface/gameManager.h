#ifndef GAME_MANAGER_H
#define GAME_MANAGER_H

#include "printer.h"
#include "inputHandler.h"
#include "../base/game.h"
#include "../base/ship.h"

template <class T, class D1, class D2>
class gameManager{
private:
    Game& game;
    Printer<D1, D2> printer;
    T handler;

    void setShips();
public: 
    gameManager(Game& g, Printer<D1, D2> p, T handler);
    void run();
};

#endif