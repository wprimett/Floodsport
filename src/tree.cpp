
//At this stage trees are simply invisable objects that set the positions of other objects
//trees grow is size as the player progresses

#include "ofApp.h"
#include "tree.hpp"

Tree::Tree(int _x, int _y, int _w, int _h):x(_x), y(_y), w(_w), h(_h){
    // Set the initial color
    //initial positions set in constructor
    x = _x;
    y = _y;
    w = _w;
    h = _h;
    
    pos.set(x, y);
}