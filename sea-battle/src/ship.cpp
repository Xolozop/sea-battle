#include <iostream>

#include "ship.h"
#include "exceptions.h"

#define TERM_DEF "\033[0m"
#define TERM_CROSSED "\033[9m"
#define TERM_GREEN "\033[32m"
#define TERM_RED "\033[31m"

int Ship::validateLength(int len) {
    if ((len < 1) || (len > 4))
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

int Ship::getState(int i) const {
    return segments[i-1];
}

void Ship::printSeg(int i) const {
    if (segments[i-1] != segStates::intact && segments[i-1] != segStates::hideDamage) {
        std::cout << TERM_RED;
        if (segments[i-1] == segStates::destroyed)
            std::cout << TERM_CROSSED;
    }   
    std::cout << 'X' << TERM_DEF;
}

void Ship::atack(int i) {
    i--;
    switch(segments[i]) {
        case segStates::intact:
            segments[i] = segStates::damaged;
            std::cout << TERM_GREEN << "Congratulations! You're damaged the ship!" << TERM_DEF << std::endl;
            break;
        case segStates::damaged:
        case segStates::hideDamage:
            segments[i] = segStates::destroyed;
            std::cout << TERM_GREEN << "Congratulations! You destroyed the ship segment!" << TERM_DEF << std::endl;
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

bool Ship::isShipDestroyed() const {
    return isDestroyed;
}

void Ship::shellAtack() {
    int i = std::rand()%length;
    while (segments[i] != segStates::intact)
        i = (i+1)%length;
    segments[i] = segStates::hideDamage;
}