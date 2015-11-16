//
//  Ship.cpp
//  Week3_apps
//
//  Created by William Primett on 20/10/2015.
//
//

#include "ship.hpp"

Ship::Ship(): x(500), y(10){
    y = ofGetHeight()/2;
    // Set the initial color
    color.set(255, 255, 255);
}

void Ship::update(float locX, float locY){
    x += locX - x;
    y += locY - y;
    //flash player when over a certain size
    //to extend into animation that resets player size
    if (size > 35){
        color.set(200, 81, 87);
        //shinks t origional size then reset colour
        while (size > 8) {
            size -= 0.1;
        }
        color.set(255, 255, 255);
    }
}

void Ship::enlarge(float rad){
    size += rad;
}

void Ship::draw(){
    ofSetCircleResolution(100);
    ofSetColor(color);
    ofFill();
    ofDrawCircle(x, y, size);
}