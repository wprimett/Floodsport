//
//  smooth.cpp
//  Week3_apps
//
//  Created by William Primett on 13/11/2015.
//
//

#include "tree.hpp"

Tree::Tree(int _x, int _y, int _w, int _h): x(_x), y(_y), w(_w), h(_h){
    // Set the initial color
    color.set(97, 127, 150, 150);
    //initial positions set in constructor
    x = _x;
    y = _y;
    w = _w;
    h = _h;
}

void Tree::draw(){
    ofSetColor(color);
    ofFill();
    ofDrawRectangle(x, y, w, h);
}