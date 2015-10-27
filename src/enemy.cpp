#include "enemy.hpp"

Enemy::Enemy(int _x, int _y, Ship *_ship): x(_x), y(_y), ship(_ship){
    // Set the initial color
    color.set( 200, 200, 200);
    
    //initial positions set in constructor
    x = _x;
    y = _y;
}

void Enemy::move(float speed){
    x += ( ship -> x - x) * speed;
    y += ( ship -> y - y) * speed;
}

void Enemy::draw(){
    ofSetColor(color);
    ofFill();
    ofCircle(x, y, 8);
}