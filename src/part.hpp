//
//  part.hpp
//  Week3_apps
//
//  Created by William Primett on 13/11/2015.
//
//

#ifndef part_hpp
#define part_hpp

#include <stdio.h>
#include "ofMain.h"

class Part {
    public:
        // Constructor
        Part(int _x, int _y, Ship *_ship);
        Ship *ship;
    
        // Methods
        void move(float speed);
        void draw();
    
        // Properties
        int x;
        int y;
        ofColor color;
        float size;
    
        protected:

    
};
#endif /* part_hpp */
