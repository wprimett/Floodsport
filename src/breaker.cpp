#include "breaker.hpp"

Breaker::Breaker(int _x, int _y, Ship *_ship): x(_x), y(_y), ship(_ship){
    // Set the initial color
    color.set( 240, 96, 96 );
    
    //initial positions set in constructor
    x = _x;
    y = _y;
    
    pos.set(x, y);
    dist = ofPoint(0,0);
    vel.set(ofRandom(-3.9, 3.9), ofRandom(-3.9, 3.9));
    drag  = ofRandom(0.95, 0.998);
}

void Breaker::move(float speed){
    ofPoint shipPos = ofPoint(ship -> x, ship -> y);
    dist = shipPos - pos;
    
    //let get the distance and only repel points close to the mouse
    dist.normalize();
    vel *= drag;
    vel += dist * speed;
    
    pos += vel;
    stayOnScreen();
}

void Breaker::stayOnScreen(){
    
    //stop particlas leaving screen
    if( pos.x > ofGetWidth() ){
        pos.x = ofGetWidth();
        vel.x *= -1.0;
    }else if( pos.x < 0 ){
        pos.x = 0;
        vel.x *= -1.0;
    }
    if( pos.y > ofGetHeight() ){
        pos.y = ofGetHeight();
        vel.y *= -1.0;
    }
    else if( pos.y < 0 ){
        pos.y = 0;
        vel.y *= -1.0;
    }
    
}

void Breaker::draw(){
    ofSetCircleResolution(100);
    ofSetColor(color);
    ofFill();
    ofDrawRectangle(pos.x, pos.y, 3, 8);
}