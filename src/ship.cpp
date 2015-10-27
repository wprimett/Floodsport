//
//  ship.cpp
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

void Ship::up(){
    y -= 4;
}

void Ship::down(){
    y += 4;
}

void Ship::draw(){
    ofSetColor(color);
    ofFill();
    ofCircle(x, y, 8);
}