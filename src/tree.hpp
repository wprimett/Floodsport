#ifndef tree_hpp
#define tree_hpp

#include "ofMain.h"

class Tree {
public:
    // Constructor
    Tree(int _x, int _y, int _w, int _h);
    
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