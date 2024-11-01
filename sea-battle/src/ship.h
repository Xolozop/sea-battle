#ifndef SHIP_H
#define SHIP_H

enum segStates {intact, hideDamage, damaged, destroyed};
enum orientation {horizontal, vertical};

class Ship 
{
private:
    int length;
    orientation orient;
    segStates* segments = nullptr;
    bool isDestroyed = false;
    int validateLength(int len);
    char validateOrientation(char ori);
public:
    Ship(int len, char ori);
    Ship(const Ship& other);
    ~Ship();
    int getLength() const;
    bool isVertical() const;
    bool hasIntactSegs() const;
    int getState(int i) const;
    void printSeg(int i) const;
    void atack(int i);
    bool isShipDestroyed() const;
    void shellAtack();
};

#endif