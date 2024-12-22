#include "field.h"

#define TERM_DEF "\033[0m"
#define TERM_UNDERLINE "\033[4m"
#define TERM_RED "\033[31m"
#define TERM_YELLOW "\033[33m"
#define TERM_RED_BG "\033[101m"

int Field::validateSize(int size) {
    if ((size < 0) || (size > 26))
        throw incorrectSizeException();
    return size;
}

Field::Field(int sz, bool isMine) : size{validateSize(sz)}, isMine{isMine} {
    fieldBlocks.resize(size);
    for (int x = 0; x < size; x++) {
        for (int y = 0; y < size; y++)
            fieldBlocks[x].push_back(blockStates::empty);
    }
}

int Field::getSize() { 
    return size;
}

Field::Field(std::vector<std::vector<int>> blocks) {
    size = blocks.size();
    fieldBlocks = blocks;
}

Field::~Field() { }

Field::Field(const Field& other) : size(other.size), isMine(other.isMine), fieldBlocks(other.fieldBlocks) { }

Field::Field(Field&& other) : size(other.size), isMine(other.isMine), fieldBlocks(std::move(other.fieldBlocks)) {
    other.size = 0;
    other.isMine = false;
}

Field& Field::operator = (const Field& other) {
    if (this != &other) {
        size = other.size;
        isMine = other.isMine;
        fieldBlocks = other.fieldBlocks;
    }
    return *this;
}

Field& Field::operator = (Field&& other) {
    if (this != &other) {
        size = other.size;
        isMine = other.isMine;
        fieldBlocks = std::move(other.fieldBlocks);
        other.size = 0;
        other.isMine = 0;
    }
    return *this;
}

int Field::charToCoord(char c) {
    return (int)c- 96;
}

void Field::validateField(shipManager manager) {
    for (size_t x = 0; x < size; x++) {
        for (size_t y = 0; y < size; y++) {
            if (fieldBlocks[x][y] > 0)
                Ship test = manager.getShip(fieldBlocks[x][y]/100, (fieldBlocks[x][y]%100)/10);
        }
    }
}

void Field::validateCoords(char coord_y, int coord_x) {
    if (!isalpha(coord_y))
        throw improperInputException();
    int x = coord_x - 1;
    int y = charToCoord(coord_y) - 1;

    if ((x < 0) || (x > size-1) || (y < 0) || (y > size-1))
        throw outOfFieldException();
}

void Field::setShip(Ship& ship, char coord_y, int coord_x, int ship_ind) {
    copyField = fieldBlocks;

    validateCoords(coord_y, coord_x);
     
    int x = coord_x - 1;
    int y = charToCoord(coord_y) - 1;
    int len = ship.getLength();
    bool ori = ship.isVertical();
    int max_x = x+len*ori;
    int max_y = y+len*!ori;
    if ((x < 0) || (max_x > size) || (y < 0) || (max_y > size))
        throw outOfFieldException();

    int x1, y1;
    // coords for loop
    for (int i = -1; i < len+1; i++) {
        x1 = x + i*ori;
        y1 = y + i*!ori;
        if ((x1-!ori > -1) && (x1-!ori < size) && (y1-ori > -1) && (y1-ori < size))
            fieldBlocks[x1-!ori][y1-ori] = blockStates::padding;
        if ((x1+!ori > -1) && (x1+!ori < size) && (y1+ori > -1) && (y1+ori < size))
            fieldBlocks[x1+!ori][y1+ori] = blockStates::padding;

        if ((i != -1) && (i != len)) {
            std::cout << i << std::endl;
            if (copyField[x1][y1] == blockStates::padding || copyField[x1][y1] > 0)
                throw invalidShipPlacementException();
            fieldBlocks[x1][y1] = len*100 + ship_ind*10 + (i+1);
        } else if ((x1 > -1) && (x1 < size) && (y1 > -1) && (y1 < size)) {
            fieldBlocks[x1][y1] = blockStates::padding;
        }
    }
}

void Field::deletePrevShip() {
    fieldBlocks = copyField;
}

std::string Field::printFieldRow(int row, bool showPaddings, shipManager manager) const {
    std::stringstream res;
    if (row == 0) {
        res << TERM_UNDERLINE << "\t  | ";
        for (int i = 0; i < size; i++)
            res << (char)(i+97) << ' ';
        res << TERM_DEF;
        return res.str();
    }
    int x = row-1;

    res << '\t';
    if (x+1 < size)
        res << ' ';
    res << x+1 << "| ";
    for (int y = 0; y < size; y++) {
        switch(fieldBlocks[x][y]) {
            case -3: // shoted
                res << TERM_RED << '*' << TERM_DEF;
                break;
            case -2: // at gunpoint
                res << TERM_RED_BG << '+' << TERM_DEF;
                break;
            case -1: // padding
                if (showPaddings && isMine) {
                    res << '\\';
                    break;
                }
            case 0: // empty
                res << (isMine ? '~' : '?');
                break;
            default:
                Ship ship = manager.getShip(fieldBlocks[x][y]/100, (fieldBlocks[x][y]%100)/10);
                int segState = ship.getState(fieldBlocks[x][y]%10);
                if (!isMine && (segState == segStates::intact || segState == segStates::hideDamage)) {
                    res << (isMine ? '~' : '?');
                } else {
                    res << ship.printSeg(fieldBlocks[x][y]%10);
                }
        }
        res << ' ';
    }
    return res.str();
}

std::string Field::saveField() const {
    std::stringstream res;

    for (int x = 0; x < size; x++) {
        for (int y = 0; y < size; y++) {
            res << fieldBlocks[x][y] << ' ';
            res << ' ';
        }
        res << std::endl;
    }
    return res.str();
}

int Field::isShip(char coord_y, int coord_x) {
    int x = coord_x - 1;
    int y = charToCoord(coord_y) - 1;
    return fieldBlocks[x][y] > 0 ? fieldBlocks[x][y] : 0;
}

int Field::isShip(int coord_y, int coord_x) {
    validateCoords((char)coord_y+97, coord_x+1);
    return fieldBlocks[coord_x][coord_y] > 0 ? fieldBlocks[coord_x][coord_y] : 0;
}

int Field::setGunpoint(char coord_y, int coord_x, shipManager& manager) {
    validateCoords(coord_y, coord_x); 
    int x = coord_x - 1;
    int y = charToCoord(coord_y) - 1;

    if (isShip(coord_y, coord_x)) {
        Ship ship = manager.getShip(fieldBlocks[x][y]/100, (fieldBlocks[x][y]%100)/10);
        if (ship.getState(fieldBlocks[x][y]%10) == segStates::destroyed)
            throw alreadyDestroyedException();
    } else {
        if (fieldBlocks[x][y] == blockStates::shoted)
            throw alreadyShootedException();
    }

    int tmp = fieldBlocks[x][y];
    fieldBlocks[x][y] = blockStates::atGunpoint;
    return tmp;
}

void Field::restoreCell(char coord_y, int coord_x, int tmp) {
    int x = coord_x - 1;
    int y = charToCoord(coord_y) - 1;
    fieldBlocks[x][y] = tmp;
}

void Field::shoot(char coord_y, int coord_x, shipManager& manager, bool& DAFlag, int tmp) {
    int x = coord_x - 1;
    int y = charToCoord(coord_y) - 1;

    if (tmp > 0) {
        fieldBlocks[x][y] = tmp;
        Ship& ship = manager.getShip(tmp/100, (tmp%100)/10);
        if (DAFlag) {
            ship.doubleAtack(tmp%10);
            DAFlag = false;
        } else {
            ship.atack(tmp%10);
        }
        
        if (ship.isShipDestroyed()) {
            bool ori = ship.isVertical();
            int x1, y1;
            for (int i = -1; i < ship.getLength()+1; i++) {
                x1 = x + i*ori;
                y1 = y + i*!ori;
                if ((x1-!ori > -1) && (x1-!ori < size) && (y1-ori > -1) && (y1-ori < size))
                    fieldBlocks[x1-!ori][y1-ori] = blockStates::shoted;
                if ((x1+!ori > -1) && (x1+!ori < size) && (y1+ori > -1) && (y1+ori < size))
                    fieldBlocks[x1+!ori][y1+ori] = blockStates::shoted;
                if ((i == -1) || (i == ship.getLength()) && (x1 > -1) && (x1 < size) && (y1 > -1) && (y1 < size))
                    fieldBlocks[x1][y1] = blockStates::shoted;
            }
        }
    } else {
        fieldBlocks[x][y] = blockStates::shoted;
    }
}