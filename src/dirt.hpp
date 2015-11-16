#ifndef dirt_hpp
#define dirt_hpp

#include "ofMain.h"

class Dirt {
public:
    // Constructor
    Dirt(int _x, int _y, int _w, int _h);
    
    // Methods
    void draw();
    
    // Properties
    int x;
    int y;
    int w;
    int h;
    ofColor color;
};
#endif