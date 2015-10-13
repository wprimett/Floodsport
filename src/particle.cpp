#include "particle.hpp"

Particle::Particle(int _x, int _y){
    // Set the initial color
    color.set( 200, 200, 200);
    
    //initial positions set in constructor
    x = _x;
    y = _y;
}

void Particle::moveTo(int locX, int locY){
    x += ( locX - x )*0.5;
    y += ( locY - y )*0.5;
}

void Particle::draw(){
    ofSetColor(color);
    ofFill();
    ofCircle(x, y, 8);
}