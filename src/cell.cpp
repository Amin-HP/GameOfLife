//
//  cell.cpp
//  gameOfLife
//
//  Created by Amin Haghpanah on 11/27/20.
//
#include "cell.h"
Cell::Cell(){
    isAlive = false;
    isSelected = false;
//    isAlive = int (ofRandom(0, 2));
}

void Cell::setup(int _id, int _x, int _y, float _size){
    x = _x;
    y = _y;
    size = _size;
    
    future = false;
    deadColor.set(ofRandom(255),ofRandom(255),ofRandom(255));
//    liveColor.set(255,255,255);
    liveColor.set(0,0,0);
    selectedColor.set(ofColor::red);
//    tone = SineWave().freq(ofMap(_id, 0, NCELLS, 20, 15000));
}
//void Cell::setNeighbours(Cell *_neighbours){
//    neighbours = _neighbours;
//}
void Cell::update(){
//    cout << ID << "(" << isAlive << ")==============================================" << endl;
//    int aliveCount = 0;
//    for(int i=0; i < 8; i++){
//        cout << neighbours[i].ID << "(" << neighbours[i].isAlive << ") | " ;
//        aliveCount += int(neighbours[i].isAlive);
//    }
//    cout << aliveCount << endl;
//    if (isAlive && (aliveCount == 2 || aliveCount == 3))
//        isAlive = true;
//    else if (!isAlive && aliveCount == 3)
//        isAlive = true;
//    else
//        isAlive = false;
    
    
    
        
}

void Cell::draw(){
    ofFill();
    if(isAlive)
        ofSetColor(liveColor);
    else
        ofSetColor(deadColor);
    ofDrawRectangle(x, y, size, size);
    
//    ofNoFill();
//    ofSetLineWidth(1);
//    if(isSelected)
//        ofSetColor(selectedColor);
//    else
//        ofSetColor(liveColor);
//    ofDrawRectangle(x, y, size, size);
    
//    ofDrawBitmapString(ofToString(ID), x + 4, y + 14);
    
}
