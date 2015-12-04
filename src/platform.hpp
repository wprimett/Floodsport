#ifndef platform_hpp
#define platform_hpp

#include "ofMain.h"
#include "ofxLiquidFun.h"

class Platform {
public:
    // Constructor
    Platform(int _x, int _y, int _w, int _h);
    
    // Methods
    void draw();
    
    // Properties
    int x;
    int y;
    int w;
    int h;
    ofColor color;
    
    ofVec2f pos;
    
};
#endif