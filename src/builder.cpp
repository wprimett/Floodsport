#include "builder.hpp"

Builder::Builder(int _x, int _y, Ship *_ship): x(_x), y(_y), ship(_ship){
    // Set the initial color
    color.set( 62, 44, 44);
    
    //initial positions set in constructor
    x = _x;
    y = _y;
    
    pos.set(x, y);
    dist = ofPoint(0,0);
    vel.set(ofRandom(-3.9, 3.9), ofRandom(-3.9, 3.9));
    drag  = ofRandom(0.95, 0.998);
    isDead = false;
}

void Builder::move(float speed){
    ofPoint shipPos = ofPoint(ship -> x, ship -> y);
    dist = shipPos - pos;
    
    //let get the distance between point and player
    dist.normalize();
    vel *= drag;
    vel += dist * speed;
    
    //add velocity to move points
    pos += vel;
    
    //updates x and y values for main program
    //is it possible to do this automatically with pointers??
    x = pos.x;
    y = pos.y;
    
    //runs function for each particle
    stayOnScreen();
    if (pos.distance( shipPos ) < ship -> size){
        isDead = true;
    }
}

void Builder::stayOnScreen(){
    
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

void Builder::kill(){
    isDead = true;
}

void Builder::draw(){
    ofSetCircleResolution(100);
    size = 2;
    ofSetColor(color);
    ofFill();
    ofDrawCircle(x, y, size);
}