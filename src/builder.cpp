#include "builder.hpp"

Builder::Builder(int _x, int _y): x(_x), y(_y){

    // Set the initial color
    color.set( 248, 230, 230);
    
    //initial positions set in constructor
    x = _x;
    y = _y;
    
    pos.set(x, y);
    dist = ofPoint(0,0);
    vel.set(ofRandom(-3.9, 3.9), ofRandom(-3.9, 3.9));
    drag  = ofRandom(0.95, 0.998);
}

//takes ship object pointer
void Builder::move(float speed, Ship *ship){
    //uses pointer to refer to ship position
    ofPoint shipPos = ofPoint(ship -> x, ship -> y);
    dist = shipPos - pos;
    
    //let get the distance between point and player
    dist.normalize();
    vel *= drag;
    vel += dist;
    
    //add velocity to move points
    pos += vel * speed;
    
    //updates x and y values for main program
    //is it possible to do this automatically with pointers??
    x = pos.x;
    y = pos.y;
    
    //runs function for each particle
    stayOnScreen();
    
    ship = new Ship;
    delete ship;
    ship = NULL;
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