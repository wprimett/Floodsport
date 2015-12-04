//
//  Ship.cpp
//  Week3_apps
//
//  Created by William Primett on 20/10/2015.
//
//

#include "ship.hpp"

Ship::Ship(): x(500), y(10) {
    y = ofGetHeight()/2;
    // Set the initial color
    color.set(248, 230, 230);
    //set start time to 0
    timeThen = 0;
    centre.set(ofGetWidth()/2, ofGetHeight()/2);
    prevLoc.set(centre.x, centre.y+300);
    
}

void Ship::update() {
    
    //flash player when over a certain size
    //to extend into animation that resets player size
    if (size > maxSize){
        reset = true;
        //shinks t origional size then reset colour
    }
    if(reset){
        if(size > 8){
            shrink(1.5);
        }else{
            //stock shinking when player resets to origional size
            color.set(255);
            reset = false;
        }
}
}

void Ship::shrink(float rad) {
    color.set(240, 96, 96 );
    size -= rad;
}

void Ship::enlarge(float rad) {
    size += rad;
}

//Player must be moving a sufficent amount to stay alive
//if player doesn't move over set time period, player registered as idle
bool Ship::checkMoving() {
    bool isMoving = true;
    timeNow = ofGetElapsedTimeMillis();
    float ellapsedTime = timeNow - timeThen;
    float dist;
    float totalDist;
    bool counterAdded;

    //set vector for current player position
    //start by comparing to player spawn position
    //get distance between points
    currLoc.set(x, y);
    dist = currLoc.distance(prevLoc);
    
    //reset timer every 5 seconds
    //update position to compare to equal current position
    if(ellapsedTime > 5000){
        prevLoc = currLoc;
        timeThen = ofGetElapsedTimeMillis();
        totalDist += dist;
        counter = 0;
    }

    if(dist < 10 & ellapsedTime < 5000){
        //only increments coutner ONCE when boolean switches
        if (counterAdded == false){
            counter ++;
            counterAdded = true;
        }else{
            //boolean reset
            counter = false;
        }
    }
    
    if(counter > 200){
        isMoving = false;
    }
   // cout << counter << endl;
    
    return isMoving;
}

//checks if player reaches the top
bool Ship::checkWon() {
    if( y - size < 1){
        hasWon = true;
    }
    
    return hasWon;
}

void Ship::draw() {
    ofSetCircleResolution(20);
    ofSetColor(color);
    ofFill();
    ofDrawCircle(x, y, size);
}