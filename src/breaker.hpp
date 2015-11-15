#ifndef breaker_h
#define breaker_h

#include "ofMain.h"
#include "ship.hpp"

class Breaker {
public:
    // Constructor
    Breaker(int _x, int _y, Ship *_ship);
    Ship *ship;
    
    // Methods
    void move(float speed);
    void draw();
    void stayOnScreen();
    
    // Properties
    int x;
    int y;
    float drag;
    
    ofColor color;
    ofPoint pos;
    ofPoint vel;
    ofPoint dist;
};
#endif
