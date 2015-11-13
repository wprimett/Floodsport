#include "enemy.hpp"

Enemy::Enemy(int _x, int _y, Ship *_ship): x(_x), y(_y), ship(_ship){
    // Set the initial color
    color.set( 200, 200, 100);
    
    //initial positions set in constructor
    x = _x;
    y = _y;
}

void Enemy::move(float speed){
    x += ( ship -> x - x) * speed;
    y += ( ship -> y - y) * speed;
}

void Enemy::draw(){
    ofSetCircleResolution(100);
    size = 2;
    ofSetColor(color);
    ofFill();
    ofDrawCircle(x, y, size);
}