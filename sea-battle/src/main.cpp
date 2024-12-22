#include <iostream>

#include "interface/inputHandler.h"
#include "interface/gameManager.h"
#include "interface/terminalInterface/termLogger.h"
#include "interface/terminalInterface/termDrawer.h"

int main() {
    srand(time(0));
    Game game;
    inputHandler comms;

    termDrawer drawer;
    termLogger logger;
    Printer<termDrawer, termLogger> printer(drawer, logger);
    
    gameManager<inputHandler, termDrawer, termLogger> manager(game, printer, comms);
    manager.run();
    return 0;
}