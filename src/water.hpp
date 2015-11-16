#ifndef water_hpp
#define water_hpp

#include "ofMain.h"

class Water {
public:
    // Constructor
    Water(int _x, int _y, int _w, int _h);
    
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