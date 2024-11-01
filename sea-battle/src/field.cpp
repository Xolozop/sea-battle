#include <iostream>
#include <climits>

#include "field.h"
#include "exceptions.h"

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

void Field::validateCoords(char coord_y, int coord_x) {
    if (!isalpha(coord_y))
        throw improperInputException();
    int x = coord_x - 1;
    int y = charToCoord(coord_y) - 1;

    if ((x < 0) || (x > size-1) || (y < 0) || (y > size-1))
        throw outOfFieldException();
}

bool Field::confirmData() const{
    std::cout << "Do you agree? (enter N to replace ship, Y or ENTER to continue): ";
    char ans = getchar();
    while ((tolower(ans) != 'n') && (ans != '\n') && (tolower(ans) != 'y')) {
        std::cerr << TERM_RED << "Incorrect value. Try again: " << TERM_DEF;
        std::cin.clear();
        std::cin.ignore(LONG_MAX, '\n');
        ans = getchar();
    }
    return (tolower(ans) != 'n');
}

void Field::setShip(Ship& ship, char coord_y, int coord_x, int ship_ind) {
    std::vector<std::vector<int>> copyField = fieldBlocks;

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
            copyField[x1-!ori][y1-ori] = blockStates::padding;
        if ((x1+!ori > -1) && (x1+!ori < size) && (y1+ori > -1) && (y1+ori < size))
            copyField[x1+!ori][y1+ori] = blockStates::padding;

        if ((i != -1) && (i != len)) {
            if (fieldBlocks[x1][y1] == blockStates::padding || fieldBlocks[x1][y1] > 0)
                throw invalidShipPlacementException();
            copyField[x1][y1] = len*100 + ship_ind*10 + (i+1);
        } else if ((x1 > -1) && (x1 < size) && (y1 > -1) && (y1 < size)) {
            copyField[x1][y1] = blockStates::padding;
        }
    }

    // if (isMine && !getAgreement())
    //     throw reEnterException();

    fieldBlocks = copyField;

}

void Field::printField(bool showPaddings, shipManager& manager) const {
    std::cout << TERM_UNDERLINE << "\t  | ";
    for (int i = 0; i < size; i++)
        std::cout << (char)(i+97) << ' ';
    std::cout << TERM_DEF;
    std::cout << std::endl;

    for (int x = 0; x < size; x++) {
        std::cout << '\t';
        if (x+1 < 10)
            std::cout << ' ';
        std::cout << x+1 << "| ";
        for (int y = 0; y < size; y++) {
            switch(fieldBlocks[x][y]) {
                case -3: // shoted
                    std::cout << TERM_RED << '*' << TERM_DEF;
                    break;
                case -2: // at gunpoint
                    std::cout << TERM_RED_BG << '+' << TERM_DEF;
                    break;
                case -1: // padding
                    if (showPaddings && isMine) {
                        std::cout << '\\';
                        break;
                    }
                case 0: // empty
                    std::cout << (isMine ? '~' : '?');
                    break;
                default:
                    Ship ship = manager.getShip(fieldBlocks[x][y]/100, (fieldBlocks[x][y]%100)/10);
                    int segState = ship.getState(fieldBlocks[x][y]%10);
                    if (!isMine && (segState == segStates::intact || segState == segStates::hideDamage)) {
                        std::cout << (isMine ? '~' : '?');
                    } else {
                        ship.printSeg(fieldBlocks[x][y]%10);
                    }
            }
            std::cout << ' ';
        }
        std::cout << std::endl;
    }
}

int Field::isShip(int y, int x) {
    return fieldBlocks[x][y] > 0 ? fieldBlocks[x][y] : -1;
}

void Field::shoot(char coord_y, int coord_x, shipManager& manager) {
    validateCoords(coord_y, coord_x);
    int x = coord_x - 1;
    int y = charToCoord(coord_y) - 1;

    if (fieldBlocks[x][y] > 0) {
        Ship ship = manager.getShip(fieldBlocks[x][y]/100, (fieldBlocks[x][y]%100)/10);
        if (ship.getState(fieldBlocks[x][y]%10) == segStates::destroyed)
            throw alreadyDestroyedException();
    } else {
        if (fieldBlocks[x][y] == blockStates::shoted)
            throw alreadyShootedException();
    }

    if (!isMine) {
        int tmp = fieldBlocks[x][y];
        fieldBlocks[x][y] = blockStates::atGunpoint;
        printField(false, manager);
        if (!confirmData()) {
            fieldBlocks[x][y] = tmp;
            throw reEnterException();
        }
        fieldBlocks[x][y] = tmp;
    }
    
    if (fieldBlocks[x][y] > 0) {
        Ship& ship = manager.getShip(fieldBlocks[x][y]/100, (fieldBlocks[x][y]%100)/10);
        ship.atack(fieldBlocks[x][y]%10);
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
            
            if (manager.isAllShipsDestroyed()) {
                if (isMine) {
                    std::cout << TERM_RED << "\tYOU'RE LOSE..." << TERM_DEF << std::endl;
                    exit(EXIT_SUCCESS);
                } else {
                    std::cout << TERM_YELLOW << "\tYOU'RE WON!!!" << TERM_DEF << std::endl;
                    exit(EXIT_SUCCESS);
                }
            }
        }
    } else {
        std::cout << "Missed." << std::endl;
        fieldBlocks[x][y] = blockStates::shoted;
    }
}