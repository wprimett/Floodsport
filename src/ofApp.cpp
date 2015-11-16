#include <algorithm>

#include "ofApp.h"

//--------------------------------------------------------------
#pragma once

#include "ofMain.h"

std::ifstream myfile (ofToDataPath("positions.txt").c_str());

void ofApp::setup(){
    //simple soundtrack imported. Would like to extend the program so that it genereates and manipulates it's own sound if I continue working on this next term
    //may consider adding basic panning or speed maniplation for this term's project
    soundtrack.load("soundtrack.mp3");
    soundtrack.setLoop(true); //Sound will loop
    soundtrack.play();
    
    //xml setup for terrain map
    ofXml XML;
    XML.load("terrain_map.xml");
    XML.setTo("terrain_map");
    
    int numPos = XML.getNumChildren();//get number of elements
        for(int i = 0; i < numPos; i++){
            //gets root of each element
            XML.setToChild(i);
            
            //finds and sets attributes for map
            string getType = XML.getAttribute("type");
            int getX = ofToInt(XML.getAttribute("x"));
            int getY = ofToInt(XML.getAttribute("y"));
            int getWidth = ofToInt(XML.getAttribute("width"));
            int getHeight = ofToInt(XML.getAttribute("height"));
            
            //creates terrain objects
            //class will use data values to formulate terrain parts to produce a set map
            terrain.push_back(Terrain(getType, getX, getY, getWidth, getHeight));
            //resets xml setting point, gets each terrain part for each iteration of the loop
            XML.setToParent();
    }
    
    // Smooth edges
    ofEnableSmoothing();
    
    // Fixed framerate
    ofSetFrameRate(60);
    
    for(int i = 0; i < 15; i++){
        builder.push_back(Builder(ofRandom(200), ofRandom(200), &ship));
        breaker.push_back(Breaker(ofRandom(200), ofRandom(200), &ship, &builder[i]));
    
    }
}

void ofApp::update(){
    if(isMute){
        soundtrack.setVolume(0);
    }else{
        soundtrack.setVolume(0.8);
    }
    
    attraction = 0.04;
    breakAtrraction = 0.01;
    
    for (auto & builders : builder){
        builders.move(attraction);
    }
    for (auto & breakers : breaker){
        breakers.move(breakAtrraction);
    }
    
    //part.move(attraction);

    if ( std::any_of(builder.begin(), builder.end(), [this](Builder builder){return ofDist(builder.x, builder.y, ship.x, ship.y) < ship.size;}))
    {
        //player grows when particcle touches, player 'eats up' particals
        ship.enlarge(0.1);
        //breakAtrraction = 0;
        //ofRemove(builder, checkDead);
}
    //removes points that touch player
    //current bug where one point of batch doesn't delete
    std::remove_if(builder.begin(), builder.end(), [this](Builder builder){return ofDist(builder.x, builder.y, ship.x, ship.y) < ship.size;});
    //plott new tree when player 'burns'
    if( ship.size > 35){
        terrain.push_back(Terrain("tree", ship.x, 720, 20, 400));
    }
}

void ofApp::draw(){
    //background centre gradient
    ofBackgroundGradient(ofColor(245, 245, 250),ofColor(190,190,195), OF_GRADIENT_CIRCULAR);
    ofPushMatrix();
    
    //player follows mouse
    ship.update(mouseX, mouseY);
    ship.draw();
    
    //part.draw();
    //draw all elements of vector objects
    for (auto & terrain : terrain){
        terrain.draw();
    }
    for (auto & builders : builder){
        builders.draw();
    }
    for (auto & breakers : breaker){
        breakers.draw();
    }
    ofPopMatrix();
}
//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    if(key == 'x') {
        newSwarm(10);
    }
    if(key == 'm'){
        isMute = !isMute;
    }
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){
    
}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){
    
}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){
    
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
    
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){
    
}

//--------------------------------------------------------------
//void ofApp::mouseEntered(int x, int y){
//
//}
//
////--------------------------------------------------------------
//void ofApp::mouseExited(int x, int y){
//
//}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){
    
}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){
    
}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){
    
}

void ofApp::newSwarm(int num){
    for(int i = 0; i < num; i++){
        //values read from file and put into class constuctor
        builder.push_back(Builder(ofRandom(200), ofRandom(200), &ship));
        breaker.push_back(Breaker(ofRandom(200), ofRandom(200), &ship, &builder[i]));
    }
}

bool ofApp::checkDead( Builder &b ){
    return b.isDead;
}