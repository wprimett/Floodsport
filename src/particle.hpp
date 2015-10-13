#ifndef ball_h
#define ball_h

#include "ofMain.h"

class Particle {
public:
    // Constructor
    Particle(int _x, int _y);
    
    // Methods
    void moveTo(int locX, int locY);
    void draw();
    
    // Properties
    int x;
    int y;
    ofColor color;
};
#endif