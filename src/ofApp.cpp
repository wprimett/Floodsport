#include <algorithm>

#include "ofApp.h"

//--------------------------------------------------------------
#pragma once

#include "ofMain.h"

std::ifstream myfile (ofToDataPath("positions.txt").c_str());

void ofApp::setup(){
    // Smooth edges
    ofEnableSmoothing();
    
    // Fixed framerate
    ofSetFrameRate(60);
    
    int readX, readY;
    
    if (myfile.is_open())
    {
        //object made for each value in file
        while ( myfile >> readX >> readY)
        {
            for(int i = 0; i < 50; i++){
                //values read from file and put into class constuctor
               // enemy.push_back(Enemy(ofRandom(200), ofRandom(200), &ship));
                ally.push_back(Ally(ofRandom(200), ofRandom(200), &ship));
            }
        }
        myfile.close();
    } else {
        std::cout << "could not load file" << std::endl;
    }
}

void ofApp::update(){
    float attraction = 0.04;
    
    for (auto & swarm : enemy){
        //swarm.move(attraction);
    }
    for (auto & swarm : ally){
        swarm.move(attraction);
    }


    if ( std::any_of(enemy.begin(), enemy.end(), [this](Enemy enemy){return ofDist(enemy.x, enemy.y, ship.x, ship.y) < ship.size;}))
    {
        ship.enlarge(0.1);
        ship.color = (255, 0, 0);
        attraction = 0.01;
    }else {
        
    }
    std::remove_if(enemy.begin(), enemy.end(), [this](Enemy enemy){return ofDist(enemy.x, enemy.y, ship.x, ship.y) < ship.size;});
}

void ofApp::draw(){
    ofBackgroundGradient(ofColor(190, 190, 190),ofColor(250,250,250), OF_GRADIENT_CIRCULAR);
    
    ship.update(mouseX, mouseY);
    ship.draw();
    
    // Now we have a method that does the drawing stuff
    for (auto & swarm : enemy){
       // swarm.draw();
    }
    for (auto & swarm : ally){
        swarm.draw();
    }
}
//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    newSwarm(10);
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
        //enemy.push_back(Enemy(ofRandom(200), ofRandom(200), &ship));
        ally.push_back(Ally(ofRandom(200), ofRandom(200), &ship));
    }
}