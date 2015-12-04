#ifndef breaker_h
#define breaker_h

#include "ofMain.h"
//point to builder header for constructor reference
#include "builder.hpp"

class Breaker {


public:
    // Constructor
    Breaker(int _x, int _y);
    
    // Methods
    void move(float speed, Builder *builder);
    void draw();
    void stayOnScreen();
    //destructor
    
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
