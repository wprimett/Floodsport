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
        for(int i = 0; i < 8; i++){
            //values read from file and put into class constuctor
            enemy.push_back(Enemy(readX, readY, &ship));
        }
        }
        myfile.close();
    } else {
        std::cout << "could not load file" << std::endl;
    }
}

void ofApp::update(){
    if ( std::any_of(enemy.begin(), enemy.end(), [this](Enemy enemy){return ofDist(enemy.x, enemy.y, ship.x, ship.y) < 80;}))
    {
                gameOver = true;
                std:cout << "gameOver";
                ship.color = (255, 0, 0);
                for (auto & swarm : enemy){
                    swarm.move(-0.01);
                }
    }else{
      for (auto & swarm : enemy){
          swarm.move(0.04);
      }
    }
    //std::remove_if(enemy.begin(), enemy.end(), [this](Enemy enemy){return enemy.x > 300;});
}

void ofApp::draw(){
    ofBackgroundGradient(ofColor(190, 190, 190),ofColor(250,250,250), OF_GRADIENT_CIRCULAR);
    
    // Now we have a method that does the drawing stuff
    for (auto & swarm : enemy){
        ship.draw();
        swarm.draw();
    }
}
//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    if(key == OF_KEY_UP){
        ship.up();
    }
    if(key == OF_KEY_DOWN){
        ship.down();
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
