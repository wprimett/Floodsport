//
//  Ship.cpp
//  Week3_apps
//
//  Created by William Primett on 20/10/2015.
//
//

#include "ship.hpp"

Ship::Ship(): x(500), y(10){
    y = 760/2;
    // Set the initial color
    color.set(255, 255, 255);
}

void Ship::update(float locX, float locY){
    x += locX - x;
    y += locY - y;
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