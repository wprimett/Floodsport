#include <algorithm>

#include "ofApp.h"

//--------------------------------------------------------------
#pragma once

#include "ofMain.h"

void ofApp::setup() {
    glEnable(GL_DEPTH);
    centre.set(ofGetWidth()/2, ofGetHeight()/2);
    font.load("mirrors.ttf", 20);
    reset.load("refresh_light.png");
    
    //simple soundtrack imported. Would like to extend the program so that it genereates and manipulates it's own sound if I continue working on this next term
    collect.load("tick.mp3");
    soundtrack.load("soundtrack.mp3");
    soundtrack.setLoop(true); //Sound will loop
    soundtrack.play();
    
    //fixed framerate
    ofSetFrameRate(60);
    
    //box2d setup
    box2d.init();
    box2d.setGravity(0, 10);
   // box2d.setFPS(30.0);
    //rigid body setup
   // box2d.registerGrabbing();
    box2d.createBounds();
    
    //fulid particle system
    particles.setParticleFlag(b2_tensileParticle);
    particles.loadImage("smoke_particle.png");
    particles.setup(box2d.getWorld(), maxParticles);
    particles.setParticleLifetime(30);
    
    //box2d circel objects to form player physics
    //this object will follow and control the position of the player
    //box2d object functions called using pointers to class
    circles.push_back(ofPtr<ofxBox2dCircle>(new ofxBox2dCircle));
    circles.back().get()->setPhysics(2.0, 0.9, 0.9);//density, bounce, friction
    circles.back().get()->setup(box2d.getWorld(), centre.x, centre.y+300, 8);

    loadMap();
    
    // Smooth edges
    ofEnableSmoothing();
    
    filter.categoryBits = 0x0001;
    filter.maskBits = 0x0000;

    //edge object made by itereating though loop
    //ground is made from many edges
    //box2d object functions called using pointers to class
    
    for (int i = 0; i < gDensity; i++){
        shared_ptr <ofxBox2dEdge> edge = shared_ptr<ofxBox2dEdge>(new ofxBox2dEdge);
                //noisy values generated
                float t = 0.0;
                float amp = 1.0;
                float step = (1.0 / gDensity) * amp;
                float gndHeight = ofNoise((i+t)/50 + 8) * 150;
                float x1 = i*(centre.x*2/gDensity);//first point
                float x2 = (i+1)*(centre.x*2/gDensity);//next / destination point
                //add verticies one by one going from left to right of screen
                edge.get()->addVertex(x1, ofGetHeight() - gndHeight);
                edge.get()->addVertex(x2, ofGetHeight() - gndHeight);
                t += step;

    //initialise edge object
    edge.get()->create(box2d.getWorld());
    //edge.get()->b2Filter(filter);
    ground.push_back(edge); //add joints to the array
        
    }
}

//--------------------------------------------------------------
void ofApp::update() {
    //update Physics
    box2d.update();
    
    ship.update();
    ofVec2f playerPos = circles.back().get()->getPosition();
    
    //mute toggle
    if(isMute){
        soundtrack.setVolume(0);
    }else{
        soundtrack.setVolume(0.8);
    }
    
    attraction = 0.04;
    breakAtrraction = 0.08;
    
    //runs moving function for all floating particels
    for (auto & builders : builder){
        builders.move(attraction);
    }
    for (auto & breakers : breaker){
        breakers.move(breakAtrraction);
    }
    
    circles.back().get()->setRadius(playerRad);
    
    //assign ship position to box2d player position for class functions
    ship.x = circles.back()->getPosition().x;
    ship.y = circles.back()->getPosition().y;
    
    if ( std::any_of(builder.begin(), builder.end(), [this](Builder builder){return ofDist(builder.x, builder.y, ship.x, ship.y) < ship.size;}))
    {
        attraction = 0.1;
        //player grows when particcle touches, player 'eats up' particals
        ship.enlarge(0.5);
        playerRad += 0.5;
        collect.play();

    }
    
    
    if ( std::any_of(breaker.begin(), breaker.end(), [this](Breaker breaker){return ofDist(breaker.pos.x, breaker.pos.y, ship.x, ship.y) < ship.size;}))
    {
        //new water molecule created when breaker object touches player
        newFlood(10);
    }
    //removes points that touch player
    //romoves using iterator loop
    for (auto & builders : builder){
        auto it = std::remove_if(
                                 builder.begin(), builder.end(),
                                 [this](Builder builder){
                                     return ofDist(builder.x, builder.y, ship.x, ship.y) < ship.size;
                                 });
        builder.erase(it, builder.end());
    }

    //removes points that touch player
    //romoves using iterator loop
    for (auto & breakers : breaker){
        auto itr = std::remove_if(
                                 breaker.begin(), breaker.end(),
                                 [this](Breaker breaker){
                                     return ofDist(breaker.pos.x, breaker.pos.y, ship.x, ship.y) < ship.size;
                                 });
        breaker.erase(itr, breaker.end());
    }


    //plott new tree when player 'burns'
    //if( ship.size > 35 || ofGetKeyPressed('v')){
    if( ship.size > 35){
        playerRad = 8;
    
        tCount ++;
        newFlood(40);
        tree.push_back(Tree(playerPos.x, ofGetHeight()  - tCount*150, 2, 200));
        bridge.clear();
        breaker.clear();
        newBridge(500, centre - centre, tree[tCount].pos, tCount);
        circles.back().get()->setPosition(playerPos.x, tree[tCount].y - 100);

    }
    //new swarm every 20 seconds
    if( ofGetFrameNum() % 1200 == 0 || builder.size() < 4){
        newSwarm(10);
    }
    
    
    resetPos.set(centre.x*2 - 100, 10);
    resetSize.set(75, 75);
}


//--------------------------------------------------------------
void ofApp::draw() {
    //background centre gradient
    ofBackgroundGradient(ofColor(17, 42, 51), ofColor(21, 51, 64),  OF_GRADIENT_LINEAR);
    reset.draw(resetPos.x, resetPos.y, resetSize.x, resetSize.y);

    ofPushMatrix();

    ofSetColor(248, 230, 230);
    //textFade("floodsport", platform[0].pos);
    
    //if ship isn't moving show message
//    if (!ship.checkMoving()) {
//        ofPushStyle();
//        ofSetColor(248, 230, 230);
//        string idle = " ";
//        idle += "get up";
//        font.drawString(idle, tree[tCount].x, tree[tCount].y);
//        ofPopStyle();
//    }
    if (ship.checkWon()){
        ofPushStyle();
        ofSetColor(248, 230, 230);
        string idle = " ";
        idle += "you win";
        font.drawString(idle, centre.x - 150, centre.y - 36);
        ofPopStyle();
    }

    //draw fluid system
    ofEnableBlendMode(OF_BLENDMODE_ADD);
    particles.draw();
    ofEnableBlendMode(OF_BLENDMODE_ALPHA);
    
    ship.draw();
    
    //draw all elements of vector objects
    for (auto & builders : builder){
        builders.draw();
    }
    for (auto & breakers : breaker){
        breakers.draw();
    }
    
    drawMap();
    ofPopMatrix();
    
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key) {
    //sountrack toggle with boolean
    if(key == 'm'){
        isMute = !isMute;
    }
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key) {
}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ) {
    
}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button) {
//    for (int i = 0; i < 20; i++) {
//        float radius = 40;
//        float x = cos(ofRandom(PI*2.0)) * radius + mouseX;
//        float y = sin(ofRandom(PI*2.0)) * radius + mouseY;
//        ofVec2f position = ofVec2f(x, y);
//        ofVec2f velocity = ofVec2f(ofRandom(-200, 200), ofRandom(-200, 200));
//        particles.createParticle(position, velocity);
//    }
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button) {
    //detects if mouse is over button object
    if( mouseX > resetPos.x && mouseX < resetPos.x + resetSize.x &&
       mouseY > resetPos.y && mouseY < resetPos.y + resetSize.y){
        
        restart();
    }
    //add ouward force for player
    //player pushes water out of the way
    ofVec2f position = circles.back().get()->getPosition();
    particles.addRepulsionForce(position, ship.size, 2.0);
    
    float g = 0.1;
    ofPoint gp = box2d.getGravity();
    float gx = ofMap(mouseX, 0, centre.x*2, -g, g); //map gravity from the center of the screen
    float gy = ofMap(position.y, 0, centre.y*2, -g, g);
    //force from above player to control bounce
    circles.back().get()->addRepulsionForce(position.x, position.y - 300, 2.0);
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button) {
}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){
    
}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){
    
}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){
    
}

void ofApp::textFade(string text, ofVec2f pos){
    ofPushStyle();
    float spacing = 5;
    float a;
    
    a = sin(theta) * 255;
    ofSetColor(248, 230, 230, a);
    string title = " ";
    title += text;
    font.drawString(title, pos.x-spacing, pos.y-spacing);
    if( a < 0 ){
        theta += 0;
    }else{
        theta += 0.02;
    }
    ofPopStyle();
    
}

void ofApp::newBridge(int num, ofVec2f start, ofVec2f end, float delta){
    float dist = start.distance(end);
    delta = delta;
    for (int i = 0; i < num; i++){
        shared_ptr <ofxBox2dEdge> face = shared_ptr<ofxBox2dEdge>(new ofxBox2dEdge);
        //noise generated and new edges are added between points
        float t = 0.0;
        float amp = 1.0;
        float step = (1.0 / num) * amp;
        float bHeight = ofNoise((i+t)/50 + 8) * 50;
        float x1 = i*(centre.x*2/num);//first point
        float x2 = (i+1)*(centre.x*2/num);//next / destination point
        //add verticies one by one going from left to right of screen
        face.get()->addVertex(x1, ofGetHeight() - bHeight * delta - tCount * 150);
        face.get()->addVertex(x2, ofGetHeight() - bHeight * delta - tCount * 150);
        t += step;
    
        //initialise edge object
        face.get()->create(box2d.getWorld());
        bridge.push_back(face); //add joints to the array
    }
}

void ofApp::newSwarm(int num){
    //new swarm of floating particles  spawns in middle
    for (int i = 0; i < num; i++) {
       //values read from file and put into class constuctor
        //takes ship address to use as pointer
        builder.push_back(Builder(ofRandom(centre.x-200, centre.x + 200),
                          ofRandom(centre.y-200, centre.y + 200), &ship));
        //each breaker point takes it's paried builder point so both groups of particles can intereact
        breaker.push_back(Breaker(ofRandom(centre.x, centre.x + 200),
                                  ofRandom(centre.y, centre.y - 200), &builder[i]));
    }
}

void ofApp::newFlood(int num){
    //new swarm of particles  spawns in middle
    for (int i = 0; i < num; i++) {
        ofVec2f position = ofVec2f(0,
                                   ofRandom(centre.y));
        ofVec2f velocity = ofVec2f(0, 0);
        particles.createParticle(position, velocity);
    }
}

void ofApp::loadMap(){
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
        if (getType == "tree" ) {
            tree.push_back(Tree(getX, getY, getWidth, getHeight));
            tHeight = getY;
        }else if (getType == "bridge" ) {
            platform.push_back(Platform(getX, getY, getWidth, getHeight));
        }
        //XML info also used for local variable values relating to the map
        else if (getType == "dirt" ) {
            
        }else if (getType == "water" ) {
            
        }

        //resets xml setting point, gets each terrain part for each iteration of the loop
        XML.setToParent();
    }
}


void ofApp::drawMap(){
    //intereact thorugh object vector arrays and call point to draw function from each
    ofSetColor(248, 230, 230);
    
    for(int i=0; i<platform.size(); i++) {
    boxes.push_back(ofPtr<ofxBox2dRect>(new ofxBox2dRect));
    boxes.back().get()->setPhysics(0, 0.63, 0.9);
    boxes.back().get()->setup(box2d.getWorld(), platform[i].x, platform[i].y, platform[i].w, platform[i].h);
    }
    
    for (int i=0; i<ground.size(); i++) {
        //points to function in class
        ground[i].get()->draw();
    }
    for (int i=0; i<boxes.size(); i++) {
        ofPushStyle();
        ofSetColor(255, 127, 127);
        boxes[i].get()->draw();
        ofPopStyle();
    }
    for (int i=0; i<bridge.size(); i++) {
        bridge[i].get()->draw();
    }

}

void ofApp::restart(){
    //reselts all positions and values
    
    circles.back().get()->setPosition(centre.x, centre.y+300);
    playerRad = 8;
    ship.size = 8;
    //reset progression counter
    tCount = 0;
    ship.counter = 0;
    tree.erase(tree.begin() + 1, tree.end());//clear all trees except first
    //remove any created objects from last game
    bridge.clear();
    builder.clear();
    breaker.clear();
    newSwarm(10);
    
    ofSetColor(248, 230, 230);
    //particles.maxCount = 0;
        
}

