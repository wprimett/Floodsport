#pragma once

#include "ofMain.h"

//Add classes
//#include "part.hpp"
#include "builder.hpp"
#include "breaker.hpp"
#include "ship.hpp"
#include "terrain.hpp"
#include "dirt.hpp"
#include "water.hpp"
#include "bridge.hpp"
#include "tree.hpp"


#include <vector>
using std::vector;

class ofApp : public ofBaseApp{
public:
    void setup();
    void update();
    void draw();
    
    void keyPressed  (int key);
    void keyReleased(int key);
    void mouseMoved(int x, int y );
    void mouseDragged(int x, int y, int button);
    void mousePressed(int x, int y, int button);
    void mouseReleased(int x, int y, int button);
    void windowResized(int w, int h);
    void dragEvent(ofDragInfo dragInfo);
    void gotMessage(ofMessage msg);
    void newSwarm(int num);
    bool checkDead(Builder &b);
    
    ofSoundPlayer soundtrack;
    bool isMute = true;
    
    
    float xPos;
    float yPos;
    float pointDist;
    float attraction;
    float breakAtrraction;
    
    //class arrays and variables
    Ship ship;
    
    //Part part;
    vector<Builder> builder;
    vector<Breaker> breaker;
    vector<Terrain> terrain;
    vector<Dirt> dirt;
    vector<Water> water;
    vector<Bridge> bridge;
    vector<Tree> tree;
};