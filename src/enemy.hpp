#include "ofMain.h"
#include "ship.hpp"

#ifndef enemy_hpp
#define enemy_hpp

class Enemy: public Part {
public:
    // Constructor
    Enemy(int _x, int _y, Ship *_ship);
    Ship *ship;
    
    // Methods
    void move(float speed);
    void draw();
    
    // Properties
    int x;
    int y;
    ofColor color;
    float size;
};
#endif