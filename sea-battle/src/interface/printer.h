#ifndef PRINTER_H 
#define PRINTER_H

#include <string>

#include "terminalInterface/termDrawer.h"
#include "terminalInterface/termLogger.h"

enum logTypes {mes, hooray, bad, error};

template <class T1, class T2>
class Printer {
private:
    T1 drawer;
    T2 logger;
public:
    Printer(T1 d, T2 l);
    void drawField(Game game, bool showPaddings=false);
    void printLog(std::string mes, logTypes type);
    void printAtackRes(atackResults res, std::string skill);
};

#endif