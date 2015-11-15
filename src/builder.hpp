#ifndef builder_h
#define builder_h

#include "ofMain.h"
#include "ship.hpp"

class Builder {
public:
    // Constructor
    Builder(int _x, int _y, Ship *_ship);
    Ship *ship;
    
    // Methods
    void move(float speed);
    void draw();
    void stayOnScreen();
    void kill();
    
    // Properties
    int x;
    int y;
    float size;
    float drag;
    bool isDead;
    
    ofColor color;
    ofPoint pos;
    ofPoint vel;
    ofPoint dist;
};
#endif