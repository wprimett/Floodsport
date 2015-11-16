#ifndef bridge_hpp
#define bridge_hpp

#include "ofMain.h"

class Bridge {
public:
    // Constructor
    Bridge(int _x, int _y, int _w, int _h);
    
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