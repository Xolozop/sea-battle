#ifndef SHIP_MANAGER_H
#define SHIP_MANAGER_H

#include <vector>

#include "ship.h"

class shipManager 
{
private:
    int amount;
    std::vector<std::vector<Ship>> ships;
public:
    shipManager(int amount, std::vector<std::vector<Ship>> shipArray);
    void refresh(Ship ship);
    bool isAllShipsEntered() const;
    int getShipIndex(int len) const;
    Ship& getShip(int x, int y);
    void printShipList() const;
    bool isAllShipsDestroyed() const;
    int* getRandomUndamagedShip() const;
};

#endif