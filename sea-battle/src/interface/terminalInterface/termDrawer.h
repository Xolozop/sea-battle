#ifndef TERM_DRAWER_H
#define TERM_DRAWER_H

#include <ostream>
#include <iomanip>

#include "../../base/game.h"

#define TERM_GREEN "\033[32m"
#define TERM_RED "\033[31m"
#define TERM_DEF "\033[0m"

class termDrawer {
public:
    void drawField(Game game, bool showPaddings=false);
};

#endif