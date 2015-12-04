#ifndef breaker_h
#define breaker_h

#include "ofMain.h"
#include "ship.hpp"
#include "builder.hpp"

class Breaker {
public:
    // Constructor
    Breaker(int _x, int _y, Builder *_builder);
    Builder *builder;
    
    // Methods
    void move(float speed);
    void draw();
    void stayOnScreen();
    //destructor
//    ~Breaker() {
//        delete builder;
//    }
    
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
