#ifndef ball_h
#define ball_h

#include "ofMain.h"
#include "ship.hpp"

class Enemy {
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
};
#endif