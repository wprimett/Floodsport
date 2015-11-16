#ifndef ally_h
#define ally_h

#include "ofMain.h"
#include "ship.hpp"

class Ally {
public:
    // Constructor
    Ally(int _x, int _y, Ship *_ship);
    Ship *ship;
    
    // Methods
    void move(float speed);
    void draw();
    
    // Properties
    int x;
    int y;
    ofColor color;
};
#endif
