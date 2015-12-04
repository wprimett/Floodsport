#pragma once

#include "ofMain.h"

//Add classes
#include "builder.hpp"
#include "breaker.hpp"
#include "ship.hpp"
#include "terrain.hpp"
#include "tree.hpp"
#include "platform.hpp"

#include <b2World.h>
#include "ofxLiquidFun.h"

#include <vector>
using std::vector;

// -------------------------------------------------

class ofApp : public ofBaseApp{
public:
    //functions
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
    void resized(int w, int h);
    void textFade(string text, ofVec2f pos);
    void newBridge(int num, ofVec2f start, ofVec2f end, float delta);
    void newSwarm(int num);
    void newFlood(int num);
    void loadMap();
    void drawMap();
    void restart();
    
    
    //button and text variables
    ofTrueTypeFont font;
    ofImage reset;
    ofPoint resetPos;
    ofPoint resetSize;
    
    //built in audio player, one object for constant backing soundtrack
    //another a sound trigger upon event
    ofSoundPlayer soundtrack;
    ofSoundPlayer collect;
    bool isMute = false;
    
    //player and attraction variables
    float playerRad = 8;
    float pointDist;
    float attraction;
    float breakAtrraction;
    ofVec2f centre;
    int gDensity = 500;
    int maxParticles = 10000;
    
    //counter variables
    //keeps track of progression, counts number of times player 'burns'
    //carried thorugh main program 
    int tCount = 0;
    float theta = 0;
    float fadeSpeed;
    
    //class arrays and variables
    Ship ship;
    
    float tHeight;
    
    //particels and set terrain objects arrays
    vector<Builder> builder;
    vector<Breaker> breaker;
    vector<Tree> tree;
    vector<Platform> platform;
    
    //box2d library objects as pointers
    ofxBox2d box2d;
    b2Filter filter;
    vector <shared_ptr<ofxBox2dEdge> > ground;
    vector <shared_ptr<ofxBox2dEdge> > bridge;
   // vector <ofPtr<ofxBox2dCircle> >	circles;    //player circle with pysics
     vector <shared_ptr<ofxBox2dCircle> >	circles;    //player circle with pysics

    ofxBox2dParticleSystem particles;			      //    LiquidFun particle system
};