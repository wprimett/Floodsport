#include "ally.hpp"

Ally::Ally(int _x, int _y, Ship *_ship): x(_x), y(_y), ship(_ship){
    // Set the initial color
    initColor.set( 255, 0, 0);
    
    //initial positions set in constructor
    x = _x;
    y = _y;
}

void Ally::move(float speed){
    x += ( ship -> x - x) * speed;
    y += ( ship -> y - y) * speed;
}

void Ally::draw(){
    ofSetCircleResolution(100);
    ofSetColor(255, 0, 0);
    ofFill();
    ofRectangle(x, y, 30, 30);
}