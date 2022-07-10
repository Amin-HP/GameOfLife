//
//  cell.h
//  gameOfLife
//
//  Created by Amin Haghpanah on 11/27/20.
//

#ifndef cell_h
#define cell_h

#include "ofMain.h"
//#include "ofxTonic.h"
//using namespace Tonic;

class Cell {

public:
    void setup(int, int, int, float);
    void update();
    void draw();
//    void setNeighbours(Cell *);
    int     ID;
    bool    isAlive;
    bool    future;
    bool    isSelected;
    float   phaseAdderTarget = 0;
//    SineWave tone;
    // variables
    Cell();
private:
    float   x;
    float   y;
    int     size;
    ofColor liveColor;
    ofColor deadColor;
    ofColor selectedColor;
    Cell    *neighbours;
};
#endif /* cell_h */
