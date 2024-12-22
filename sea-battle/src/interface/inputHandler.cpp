#include "inputHandler.h"

inputHandler::inputHandler() {
    try {
        File file("commands.txt");
        std::stringstream str = file.read();
        size_t i = 0;
        char com;
        while (str >> com) {
            auto it = commandMap.find(com);
            if (it != commandMap.end())
        throw std::runtime_error("Key for command is reserved! Default values will be used.");
            commandMap[com] = static_cast<commands>(i);
            i++;
        }
        if (i < 4)
            throw std::runtime_error("Miss key for one of the commands! Default values will be used.");
    } catch (const fileWriteException& e) {
        commandMap['e'] = commands::quit;
        commandMap['a'] = commands::atack;
        commandMap['q'] = commands::skill;
        commandMap['s'] = commands::save; 
    }
    catch (const std::exception& e) {
        std::cerr << e.what() << std::endl;
        commandMap['e'] = commands::quit;
        commandMap['a'] = commands::atack;
        commandMap['q'] = commands::skill;
        commandMap['s'] = commands::save;
    }
}

commands inputHandler::getCommand() {
    std::cout << "Input command: ";
    char comm;
    std::cin >> comm;
    comm = tolower(comm);

    auto it = commandMap.find(comm);
    if (it == commandMap.end())
        throw std::runtime_error("Not a command!");
    return it->second;
}


int inputHandler::getLen() {
    std::cout << "Please, enter ship length: ";
    int len;
    if (!(std::cin >> len))
        throw impoperLenException();
    Ship tmp(len, 'v');
    return len;
}

char inputHandler::getOri() {
    std::cout << "Enter ship orientation [v/h]: ";
    char ori;
    if (!(std::cin >> ori))
        throw impoperOriException();
    ori = tolower(ori);
    Ship tmp(2, ori);
    return ori;
}

bool inputHandler::getAgreement() {
    std::cout << "Do you argee? [y/n]: ";
    char ans;
    std::cin >> ans;
    ans = tolower(ans);
    if ((ans != 'n') && (ans != 'y'))
        throw improperInputException();
    return (ans == 'n') ? false : true; 
}

coord_t inputHandler::getCoords() {
    std::cout << "Please, enter coordinates in format `letter digit`: ";
    coord_t coords;
    if (!(std::cin >> coords.ver >> coords.hor))
        throw std::runtime_error("Incorrect coordinates!");
    return coords;
}
