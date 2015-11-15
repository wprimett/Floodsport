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
        XML.setToChild(i);
        
        string getType = XML.getAttribute("type");
        float getX = ofToInt(XML.getAttribute("x"));
        float getY = ofToInt(XML.getAttribute("y"));
        float getWidth = ofToInt(XML.getAttribute("width"));
        float getHeight = ofToInt(XML.getAttribute("hight"));
        cout << "new terrain of type: " << getType << getX;

        terrain.emplace_back(Terrain(getType, getX, getY, getWidth, getHeight));
        XML.setToParent();
    }
    
    
    // Smooth edges
    ofEnableSmoothing();
    
    // Fixed framerate
    ofSetFrameRate(60);
    
    for(int i = 0; i < 15; i++){
        builder.push_back(Builder(ofRandom(200), ofRandom(200), &ship));
        breaker.push_back(Breaker(ofRandom(200), ofRandom(200), &ship));
    
    }
}

void ofApp::update(){
    if(isMute){
        soundtrack.setVolume(0);
    }else{
        soundtrack.setVolume(0.8);
    }
    
    attraction = 0.02;
    
    for (auto & builders : builder){
        builders.move(attraction);
    }
    for (auto & destructors : breaker){
        destructors.move(attraction/2);
    }
    
    //part.move(attraction);

    if ( std::any_of(builder.begin(), builder.end(), [this](Builder builder){return ofDist(builder.x, builder.y, ship.x, ship.y) < ship.size;}))
    {

        
        ship.enlarge(0.1);
        //ship.color = (255, 0, 0);
        attraction = 0.005;
        builder.kill();
        //std::remove_if(builder.begin(), builder.end(), [this](Builder builder){return ofDist(builder.x, builder.y, ship.x, ship.y) < ship.size;});
}
    ofRemove(builder, isDead);
}

void ofApp::draw(){
    //background centre gradient
    ofBackgroundGradient(ofColor(245, 245, 250),ofColor(190,190,195), OF_GRADIENT_CIRCULAR);
    
    ship.update(mouseX, mouseY);
    ship.draw();
    
    //part.draw();
    // Now we have a method that does the drawing stuff
    for (auto & water : terrain){
        water.draw();
    }
    for (auto & builders : builder){
        builders.draw();
    }
    for (auto & destructors : breaker){
        destructors.draw();
    }

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
        breaker.push_back(Breaker(ofRandom(200), ofRandom(200), &ship));
    }
}