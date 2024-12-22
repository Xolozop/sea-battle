#include "printer.h"

template <class T1, class T2>
Printer<T1, T2>::Printer(T1 d, T2 l) : drawer{d}, logger{l} { }

template <class T1, class T2>
void Printer<T1, T2>::drawField(Game game, bool showPaddings) {
    drawer.drawField(game, showPaddings);
}

template <class T1, class T2>
void Printer<T1, T2>::printLog(std::string mes, logTypes type) {
    switch (type) {
        case logTypes::hooray:
            logger.printHooray(mes);
            break;
        case logTypes::error:
            logger.printError(mes);
            break;
        case logTypes::bad:
            logger.printBad(mes);
            break;
        default:
            logger.printMes(mes);
    }
}

template <class T1, class T2>
void Printer<T1, T2>::printAtackRes(atackResults res, std::string skill) {
    logger.printAtackRes(res, skill);
}

template class Printer<termDrawer, termLogger>;