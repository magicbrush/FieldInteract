#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    screenW = ofGetWidth();
    screenH = ofGetHeight();
    
    _FCoef.allocate(screenW, screenH, OF_IMAGE_GRAYSCALE);
    _FCoef.load("Coef.jpg");
    _FCoef.resize(screenW,screenH);
    _FCoef.update();
    
    
    _FWave.allocate(screenW, screenH, OF_IMAGE_GRAYSCALE);
    _FWave.load("Wave.jpg");
    _FWave.resize(screenW,screenH);
    _FWave.update();
    
    _FSpd.allocate(screenW, screenH, OF_IMAGE_GRAYSCALE);
    _FSpd.setColor(ofFloatColor(0,0,0,0));
    _FSpd.update();
    
    _FWaveDisp.allocate(screenW,screenH,OF_IMAGE_GRAYSCALE);
    _FSpd.setColor(ofFloatColor(0,0,0,0));
    _FSpd.update();
    
    _coef.set("Coef",0.8f,0.0f,5.0f);
    _dispOffset.set("DispOffset",0.3f,-1.0f,1.0f);
    _dispScale.set("DispScale",1.0f,0.1f,5.0f);
    _Control.setName("Control");
    _Control.add(_coef);
    _Control.add(_dispOffset);
    _Control.add(_dispScale);
    _GUI.setup("GUI");
    _GUI.add(_Control);
    _GUI.setPosition(0,0);
    _GUI.setShape(0,0,200,400);

}

//--------------------------------------------------------------
void ofApp::update(){
    float dt = ofGetLastFrameTime();
    
    for(int mm=0;mm<1;mm++)
    {
    for(int i=0;i<screenW;i++)
    {
        for(int j=0;j<screenH;j++)
        {
            ofVec2f Coord(i,j);
            ofFloatColor W = _FWave.getColor(i,j);
            float w = W.getBrightness();
            
            ofVec2f NB[4] = {ofVec2f(-1,0),ofVec2f(1,0),ofVec2f(0,-1),ofVec2f(0,1)};
            float deltaW = 0.0f;
            for(int m=0;m<4;m++)
            {
                ofVec2f CoordN = Coord+NB[m];
                CoordN.x = ofWrap(CoordN.x,0,screenW);
                CoordN.y = ofWrap(CoordN.y,0,screenH);
                ofFloatColor WN = _FWave.getColor(CoordN.x,CoordN.y);
                float wn = WN.getBrightness();
                deltaW += wn-w;
            }
            
            ofFloatColor CCoef = _FCoef.getColor(i,j);
            float coef = CCoef.getBrightness();
            float acc = _coef*coef*deltaW/4.0f;
            
            ofFloatColor CSpd = _FSpd.getColor(i,j);
            float spd = CSpd.getBrightness();
            spd = ofClamp(spd,-5,5);
            w += spd*dt;
            //w = ofWrap(w,-10,10);
            _FWave.setColor(i, j, ofFloatColor(w,1.0f));
            spd += acc*dt;
            //spd = ofWrap(spd,-10,10);
            _FSpd.setColor(i,j,ofFloatColor(spd,1.0f));
            
            float ds = pow(10.0f,-_dispScale);
            float spdDisp = spd*ds+ _dispOffset;
            _FWaveDisp.setColor(i,j,ofFloatColor(spdDisp,1.0f));
        }
    }
    _FSpd.update();
    _FWave.update();
        _FWaveDisp.update();
    }

}

//--------------------------------------------------------------
void ofApp::draw(){
    
    _FWaveDisp.draw(0,0,ofGetWidth(),ofGetHeight());
    
    _GUI.draw();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

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
    //ofSetWindowShape(screenW, screenH);
}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
