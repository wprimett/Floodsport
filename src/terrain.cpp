#include "terrain.hpp"

Terrain::Terrain(string _type, int _x, int _y, int _w, int _h): type(_type), x(_x), y(_y), w(_w), h(_h){
    // Set the initial color
    color.set(97, 127, 150, 150);
    //initial positions set in constructor
    type = _type;
    x = _x;
    y = _y;
    w = _w;
    h = _h;
}

void Terrain::draw(){
    ofSetColor(color);
    ofFill();
    ofDrawRectangle(x, y, w, h);
}