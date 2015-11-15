#ifndef terrain_hpp
#define terrain_hpp

#include "ofMain.h"

class Terrain {
public:
    // Constructor
    Terrain(string type, int _x, int _y, int _w, int _h);
    
    // Methods
    void draw();
    
    // Properties
    int x;
    int y;
    int w;
    int h;
    string type;
    ofColor color;
};
#endif