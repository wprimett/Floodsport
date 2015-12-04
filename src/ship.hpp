
#ifndef ship_hpp
#define ship_hpp

#include <stdio.h>
#include "ofMain.h"
#include "ofxLiquidFun.h"

class Ship {
public:
    // Constructor
    Ship();
    
    // Methods
    void update();
    void shrink(float rad);
    void enlarge(float rad);
    bool checkMoving();
    bool checkWon();
    void draw();
    
    // Properties
    int x;
    int y;
    ofVec2f pos;
    float size = 8;
    ofColor color;
    
    ofVec2f centre;
    
    int maxSize = 35;
    bool reset = false;
    
    //timer and position change variables
    float timeNow;
    float timeThen;
    ofPoint currLoc;
    ofPoint prevLoc;
    int counter = 0;
    bool counterAdded = false;
    
    bool hasWon = false;
    
};

#endif /* player_hpp */
