#include "terrain.hpp"

Terrain::Terrain(int _x, int _y, int _w, int _h): x(_x), y(_y), w(_w), h(_h){
    // Set the initial color
    
    //initial positions set in constructor
    x = _x;
    y = _y;
    w = _w;
    h = _h;
}

void Terrain::draw(){
    ofSetColor(255, 0, 0);
    ofFill();
    ofRectangle(x, y, w, h);
}