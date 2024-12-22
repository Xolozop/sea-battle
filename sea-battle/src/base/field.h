#ifndef FIELD_H
#define FIELD_H

#include "ship.h"
#include "shipManager.h"
#include "exceptions.h"

enum blockStates {shoted=-3, atGunpoint=-2, padding=-1, empty=0};
class Field 
{
private:
    int size;
    std::vector<std::vector<int>> fieldBlocks;
    std::vector<std::vector<int>> copyField;
    int charToCoord(char c);
    int validateSize(int size);
public:
    bool isMine;
    Field(int size, bool isMine);
    Field(std::vector<std::vector<int>> blocks);
    int getSize();

    Field(const Field& other);
    Field(Field&& other);
    Field& operator=(const Field& other);
    Field& operator=(Field&& other);
    ~Field();

    void validateField(shipManager manager);
    void validateCoords(char coord_y, int coord_x);
    std::string printFieldRow(int row, bool showPaddings, shipManager manager) const;
    std::string saveField() const;
    void setShip(Ship& ship, char coord_y, int coord_x, int ship_ind);
    void deletePrevShip();
    int isShip(char coord_y, int coord_x);
    int isShip(int coord_y, int coord_x);

    int setGunpoint(char coord_y, int coord_x, shipManager&);
    void restoreCell(char coord_y, int coord_x, int tmp);
    void shoot(char coord_y, int coord_x, shipManager& manager, bool& DAFlag, int tmp);
};

#endif 