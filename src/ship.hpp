
#ifndef ship_hpp
#define ship_hpp

#include <stdio.h>
#include "ofMain.h"

class Ship {
public:
    // Constructor
    Ship();
    
    // Methods
    void update(float locX, float locY);
    void enlarge(float rad);
    void draw();
    
    // Properties
    int x;
    int y;
    float size = 8;
    ofColor color;
};

#endif /* player_hpp */
