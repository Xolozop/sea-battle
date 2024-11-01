#ifndef FIELD_H
#define FIELD_H

#include "ship.h"
#include "shipManager.h"

enum blockStates {shoted=-3, atGunpoint=-2, padding=-1, empty=0};
class Field 
{
private:
    int size;
    std::vector<std::vector<int>> fieldBlocks;
    int charToCoord(char c);
    bool confirmData() const;
    int validateSize(int size);
public:
    bool isMine;
    Field(int size, bool isMine);
    Field(const Field& other);
    Field(Field&& other);
    Field& operator=(const Field& other);
    Field& operator=(Field&& other);
    ~Field();
    void validateCoords(char coord_y, int coord_x);
    void printField(bool showPaddings, shipManager& manager) const;
    void setShip(Ship& ship, char coord_y, int coord_x, int ship_ind);
    int isShip(int coord_y, int coord_x);
    void shoot(char coord_y, int coord_x, shipManager& manager);
};

#endif 