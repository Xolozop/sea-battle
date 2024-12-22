#include <iostream>

#include "ship.h"
#include "exceptions.h"

#define MAX_SHIP_LEN 4

#define TERM_DEF "\033[0m"
#define TERM_CROSSED "\033[9m"
#define TERM_ORANGE "\033[33m"
#define TERM_GREEN "\033[32m"
#define TERM_RED "\033[31m"

int Ship::validateLength(int len) {
    if ((len < 1) || (len > MAX_SHIP_LEN))
        throw impoperLenException();
    return len;
}

char Ship::validateOrientation(char ori) {
    if ((ori != 'h') && (ori != 'v'))
        throw impoperOriException();
    return ori;
}

Ship::Ship(int len, char ori) : length{validateLength(len)} {
    validateOrientation(ori);
    segments = new segStates[length];
    for (int i = 0; i < length; i++)
        segments[i] = segStates::intact;
    orient = (ori == 'h') ? orientation::horizontal : orientation::vertical;
}

Ship::~Ship() {
    if (segments != nullptr)
        delete[] segments;
}

Ship::Ship(const Ship& other) : length(other.length), orient(other.orient) {
    delete[] segments;
    if (other.segments != nullptr) {
        segments = new segStates[length];
        for(int i = 0; i < length; i++)
            segments[i] = other.segments[i];
    }
}


int Ship::getLength() const {
    return length;
}

bool Ship::isVertical() const {
    return orient == orientation::vertical;
}

bool Ship::hasIntactSegs() const {
    for (int i = 0; i < length; i++) {
        if (segments[i] == segStates::intact) 
            return true; 
    }
    return false;
}

segStates Ship::getState(int i) const {
    return segments[i-1];
}

void Ship::setState(int i, int state) {
    if (state < 0 || state > 3)
        throw fileReadException();
    segments[i-1] = static_cast<segStates>(state);
}

std::string Ship::printSeg(int i) const {
    std::stringstream seg;
    i--;
    if (segments[i] == segStates::damaged || segments[i] == segStates::destroyed) {
        seg << TERM_RED;
        if (segments[i] == segStates::destroyed)
            seg << TERM_CROSSED;
    } 
    if (segments[i] == segStates::intact || segments[i] == segStates::hideDamage)
        seg << TERM_ORANGE;
    seg << 'X' << TERM_DEF;
    return seg.str();
}

void Ship::atack(int i) {
    i--;
    switch(segments[i]) {
        case segStates::intact:
            segments[i] = segStates::damaged;
            break;
        case segStates::damaged:
        case segStates::hideDamage:
            segments[i] = segStates::destroyed;
            for (int x = 0; x < length; x++) {
                if (segments[x] != segStates::destroyed) 
                    return;
            }
            isDestroyed = true;
            break;
        default:
            throw alreadyDestroyedException();
    }
}


void Ship::doubleAtack(int i) {
    i--;
    if (segments[i] != segStates::destroyed) {
        segments[i] = segStates::destroyed;
        for (int x = 0; x < length; x++) {
            if (segments[x] != segStates::destroyed) 
                return;
        }
        isDestroyed = true;
    } else {
        throw alreadyDestroyedException();
    }
}

bool Ship::isShipDestroyed() const {
    return isDestroyed;
}

void Ship::shellAtack() {
    int i = std::rand()%length;
    while (segments[i] != segStates::intact)
        i = (i+1)%length;
    segments[i] = segStates::hideDamage;
}