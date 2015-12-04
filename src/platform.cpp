
#include "ofApp.h"
#include "platform.hpp"

Platform::Platform(int _x, int _y, int _w, int _h):x(_x), y(_y), w(_w), h(_h){
    // Set the initial color
    //initial positions set in constructor
    x = _x;
    y = _y;
    w = _w;
    h = _h;
    
    pos.set(x, y);
}

void Platform::draw(){
    color.set(255, 127, 127);
    ofSetColor(color);
    ofDrawRectangle(x, y, 1, w, h);
}