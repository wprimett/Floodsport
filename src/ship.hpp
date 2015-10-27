//
//  ship.hpp
//  Week3_apps
//
//  Created by William Primett on 20/10/2015.
//
//

#ifndef ship_hpp
#define ship_hpp

#include <stdio.h>
#include "ofMain.h"

class Ship {
public:
    // Constructor
    Ship();
    
    // Methods
    void up();
    void down();
    void draw();
    
    // Properties
    int x;
    int y;
    ofColor color;
};

#endif /* ship_hpp */
