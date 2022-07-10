#pragma once

#include "ofMain.h"
#include "cell.h"
#include "ofxOpenCv.h"
//#include "ofxTonic.h"
//using namespace Tonic;
#define NCELLS 185

//#define _USE_LIVE_VIDEO
#define _USE_VIDEO
//#define _USE_IMAGE

class ofApp : public ofBaseApp{
//    ofxTonicSynth synth;
    
public:
    void setup();
    void update();
    void draw();

    void keyPressed(int key);
    void keyReleased(int key);
    void mouseMoved(int x, int y );
    void mouseDragged(int x, int y, int button);
    void mousePressed(int x, int y, int button);
    void mouseReleased(int x, int y, int button);
    void mouseEntered(int x, int y);
    void mouseExited(int x, int y);
    void windowResized(int w, int h);
    void dragEvent(ofDragInfo dragInfo);
    void gotMessage(ofMessage msg);
//    void audioRequested (float * output, int bufferSize, int nChannels);
    
    Cell cells[NCELLS][NCELLS];
    float cellSize = 4;
    int cellMargin = 0;
    int x0 = 0;
    int y0 = 0;
    
    float startTime = 0;
    bool timerEnd = false;
    float tickTime = 30;
    
    float scanStart = 0, scanTickTime = 60;
    int row = 0;
    
    void updateCells();
    void updateScan(int);
//    Cell* getNeighbours(Cell[NCELLS][NCELLS], int, int);
    
#if defined(_USE_LIVE_VIDEO)
    ofVideoGrabber          vidGrabber;
#elif defined(_USE_VIDEO)
    ofVideoPlayer           vidPlayer;
#elif defined(_USE_IMAGE)
    ofImage                 img;
#endif
    
    ofxCvColorImage         colorImg;
    ofxCvGrayscaleImage     grayImage;
    ofxCvGrayscaleImage     grayBg;
    ofxCvGrayscaleImage     grayDiff;
    ofxCvGrayscaleImage     grayEmpty;
    
    int     threshold;
    bool    bLearnBakground;
    bool    isStart = true;
    bool    isFirst = true;
    
    
		
};
