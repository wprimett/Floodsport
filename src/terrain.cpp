#include "terrain.hpp"

Terrain::Terrain(string _type, int _x, int _y, int _w, int _h): type(_type), x(_x), y(_y), w(_w), h(_h){
    // Set the initial color
    //initial positions set in constructor
    type = _type;
    x = _x;
    y = _y;
    w = _w;
    h = _h;
}

void Terrain::findType() {
    //diffent shapes drawn deoendant on type
    //would like to have these as subclasses at some point
    
    if ( type == "dirt" ) {
        ofSetColor(color);
        ofNoFill();
        //generative terrain from noise
        ofPushMatrix();
        ofBeginShape();
        for (int i=0; i < w; i++) {
            float t = 0.0;
            float step = 0.006;
            float gndHeight = ofNoise((i+t)/200 + 8) * 150;
            
            color.set(92, gndHeight*255, 81);
            ofVertex(i, ofGetHeight());
            ofVertex(i, ofGetHeight() - gndHeight);
            t+=step;
        }
        ofEndShape();
        ofPopMatrix;

    }else if( type == "water"){
        color.set(140, 190, 178, 150);
        ofSetColor(color);
        ofDrawRectangle(x, y, w, h);
    }else if( type == "bridge"){
        color.set(255, 255, 255);
        ofSetColor(color);
        ofDrawRectangle(x, y, w, h);
    }else if( type == "tree"){
        color.set(242, 235, 191);
        ofSetColor(color);
        ofDrawRectangle(x, y, w, h);
    }
}

void Terrain::draw(){
    findType();
    //ofDrawRectangle(x, y, w, h);
}