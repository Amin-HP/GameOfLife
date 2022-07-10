#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
//    ofSoundStreamSetup(2, 0, this, 44100, 256, 4);
//    SineWave tone = SineWave().freq(500);
//    synth.setOutputGen( tone );
    ofSetWindowShape(NCELLS * (cellSize + cellMargin), NCELLS * (cellSize + cellMargin));
    for (int i = 0; i < NCELLS; i++) {
        for (int j = 0; j < NCELLS; j++) {
            int c = j + i * NCELLS;
            cells[j][i].setup(c, x0 + j * (cellSize + cellMargin), y0 + i * (cellSize + cellMargin), cellSize);
        }
    }
    
    startTime = ofGetElapsedTimeMillis();
    
#if defined(_USE_LIVE_VIDEO)
    vidGrabber.setVerbose(true);
    vidGrabber.setup(NCELLS,NCELLS);
#elif defined(_USE_VIDEO)
    vidPlayer.load("disolve2.mov");
    vidPlayer.play();
    vidPlayer.setLoopState(OF_LOOP_NORMAL);
#elif defined(_USE_IMAGE)
    img.load("logo.png");
#endif
    
    colorImg.allocate(NCELLS,NCELLS);
    grayImage.allocate(NCELLS,NCELLS);
    grayBg.allocate(NCELLS,NCELLS);
    grayDiff.allocate(NCELLS,NCELLS);
    grayEmpty.allocate(NCELLS,NCELLS);
    
    bLearnBakground = false;
    grayBg = grayEmpty;
    threshold = 100;
    

}

//--------------------------------------------------------------
void ofApp::update(){
    
    
    
    bool bNewFrame = false;
    
#if defined(_USE_LIVE_VIDEO)
   vidGrabber.update();
   bNewFrame = vidGrabber.isFrameNew();
#elif defined(_USE_VIDEO)
    vidPlayer.update();
    bNewFrame = vidPlayer.isFrameNew();
#elif defined(_USE_IMAGE)
    bNewFrame = true;
#endif
    
    if (bNewFrame){
        
    #if defined(_USE_LIVE_VIDEO)
        colorImg.setFromPixels(vidGrabber.getPixels());
    #elif defined(_USE_VIDEO)
        colorImg.setFromPixels(vidPlayer.getPixels());
    #elif defined(_USE_IMAGE)
        colorImg.setFromPixels(img.getPixels());
    #endif
    
    #if !defined(_USE_IMAGE)
        colorImg.resize(NCELLS, NCELLS);
        grayImage = colorImg;
        
        if (bLearnBakground == true){
            grayBg = grayImage;        // the = sign copys the pixels from grayImage into grayBg (operator overloading)
            bLearnBakground = false;
        }
        
        grayDiff.absDiff(grayBg, grayImage);
        grayDiff.threshold(threshold);
    #else
        colorImg.resize(NCELLS, NCELLS);
        grayImage = colorImg;
//        if(isFirst)
        grayDiff = grayImage;
    #endif
    }
    float timer = ofGetElapsedTimeMillis() - startTime;
    if (timer > tickTime){
        if(isStart || isFirst){
            updateCells();
            isFirst = false;
        }
        startTime = ofGetElapsedTimeMillis();
    }
    
    float scanTimer = ofGetElapsedTimeMillis() - scanStart;
    if (scanTimer > scanTickTime){
        updateScan(row);
        row = (row + 1) % NCELLS;
        scanStart = ofGetElapsedTimeMillis();
    }
}

//--------------------------------------------------------------
void ofApp::updateCells(){
//    Generator frequency;
    for (int i = 0; i < NCELLS; i++) {
        for (int j = 0; j < NCELLS; j++) {
//            if(cells[j][i].isAlive)
//                synth.setOutputGen(cells[j][i].tone);
//            cout << endl <<cells[j][i].ID << "(" << cells[j][i].isAlive << ") ==============================" << endl;
            int aliveCount = 0;
            for (int q = i - 1; q <= i + 1; q ++) {
                for (int w = j - 1; w <= j + 1; w ++) {
                    if (q >= 0 && w >= 0 && q < NCELLS && w < NCELLS && ( w != j || q != i) ){
//                        cout << cells[w][q].ID << "(" << cells[w][q].isAlive << ") | ";
                        aliveCount += int(cells[w][q].isAlive);
                    }
                }
            }
//            cout << aliveCount;
            
            if (cells[j][i].isAlive && (aliveCount == 2 || aliveCount == 3))
                cells[j][i].future = true;
            else if (!cells[j][i].isAlive && aliveCount == 3)
                cells[j][i].future = true;
            else
                cells[j][i].future = false;
        }
    }
//    unsigned char * pixels = grayDiff.getPixels();
//    synth.setOutputGen( frequency );
    auto pixels = grayDiff.getPixels();
    for (int i = 0; i < NCELLS; i++) {
        for (int j = 0; j < NCELLS; j++) {
            cells[j][i].isAlive = cells[j][i].future | (bool)pixels[i * NCELLS + j];
            
//            cells[j][i].isAlive = (bool)pixels[i * NCELLS + j];
        }
    }
}
//--------------------------------------------------------------
void ofApp::updateScan(int row){
    int prvRow = (row == 0) ? NCELLS - 1 : row - 1;
    for (int i = 0; i < NCELLS; i++) {
        cells[i][row].isSelected = true;
        cells[i][prvRow].isSelected = false;
//        cout << cells[i][row].isAlive << " ";
    }
//    cout << endl;
}
//--------------------------------------------------------------
void ofApp::draw(){
    
    
    
    for (int i = 0; i < NCELLS ; i++) {
        for (int j = 0; j < NCELLS ; j++) {
            cells[j][i].draw();
        }
    }
    
    ofSetHexColor(0xffffff);
//    colorImg.draw(1010,10);
//    grayImage.draw(1010,110);
//    grayBg.draw(1010,210);
//    grayDiff.draw(1010,310);
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    switch (key){
        case ' ':
            bLearnBakground = true;
            break;
        case '+':
            threshold ++;
            if (threshold > 255) threshold = 255;
            break;
        case '-':
            threshold --;
            if (threshold < 0) threshold = 0;
            break;
        case 'r':
            #if defined(_USE_VIDEO)
                vidPlayer.stop();
                vidPlayer.play();
            #endif
            grayBg = grayEmpty;
            for (int i = 0; i < NCELLS; i++) {
                for (int j = 0; j < NCELLS; j++) {
                    cells[j][i].isAlive =  false;
        //            updateCells();
                }
            }
            break;
    }
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
    isStart = true;
    grayDiff = grayImage;
//    for (int i = 0; i < NCELLS; i++) {
//        for (int j = 0; j < NCELLS; j++) {
//            cells[j][i].isAlive =  int(ofRandom(0, 2));
////            updateCells();
//        }
//    }
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

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

//--------------------------------------------------------------
//Cell* ofApp::getNeighbours(Cell _cells[][NCELLS + 2], int _x, int _y){
//    Cell *res = (Cell *)malloc(8 * sizeof(Cell));
//    int c = 0;
//    for (int i = _y - 1; i <= _y + 1; i ++) {
//        for (int j = _x - 1; j <= _x + 1; j ++) {
//            if( j != _x || i != _y){
//                res[c++] = _cells[j][i];
//            }
//        }
//    }
//    return res;
//}

//--------------------------------------------------------------
//void ofApp::audioRequested (float * output, int bufferSize, int nChannels){
//    synth.fillBufferOfFloats(output, bufferSize, nChannels);
//    
//}
