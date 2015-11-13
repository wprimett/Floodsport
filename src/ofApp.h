#pragma once

#include "ofMain.h"

//Add classes
#include "part.hpp"
#include "enemy.hpp"
#include "ship.hpp"
#include "ally.hpp"
#include "terrain.hpp"

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
    
    float xPos;
    float yPos;
    
    //class arrays and variables
    vector<Enemy> enemy;
    vector<Ally> ally;
    //vector<Terrain> terrain;
    Ship ship;
    
    

};