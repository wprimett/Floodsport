#include "breaker.hpp"

Breaker::Breaker(int _x, int _y, Builder *_builder): x(_x), y(_y), builder(_builder){
    // Set the initial color
    color.set( 255, 127, 127 );
    
    //initial positions set in constructor
    x = _x;
    y = _y;
    
    pos.set(x, y);
    dist = ofPoint(0,0);
    vel.set(ofRandom(-3.9, 3.9), ofRandom(-3.9, 3.9));
    drag  = ofRandom(0.95, 0.998);
}

void Breaker::move(float speed){
    float uniqueVal = ofRandom(-10000, 10000);
    
    ofPoint shipPos = ofPoint(builder -> x, builder -> y);
    dist = shipPos - pos;
    
    dist.normalize();
    vel *= drag;
    vel += dist * speed;
    
    //based of example template for now
    //repels from builder parts
    if( pos.distance(shipPos) < 150 ){
        vel += -dist * 0.6; //repel points
    }else{
        dist.x = ofSignedNoise(uniqueVal, pos.y * 0.01, ofGetElapsedTimef()*0.2);
        dist.y = ofSignedNoise(uniqueVal, pos.x * 0.01, ofGetElapsedTimef()*0.2);
        vel += dist * 0.04;
    }
    
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
    if( pos.y > ofGetHeight()){
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