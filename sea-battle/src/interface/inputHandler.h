#ifndef INPUT_HANDLER_H
#define INPUT_HANDLER_H

#include <sstream>
#include <unordered_map>

#include "../base/file.h"
#include "../base/ship.h"
#include "../base/game.h"

enum commands {atack, skill, save, quit};

class inputHandler {
private:
    std::unordered_map<char, commands> commandMap;
    
public:
    inputHandler();
    commands getCommand();
    
    int getLen();
    char getOri();
    bool getAgreement();
    coord_t getCoords();
};

#endif