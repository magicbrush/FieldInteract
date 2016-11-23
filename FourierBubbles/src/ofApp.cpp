#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    int w,h;
    w = ofGetWidth();
    h = ofGetHeight();
    for(int i=0;i<3;i++)
    {
        ofFloatImage A,F,P;
        A.load("A"+ofToString(i) + ".jpg");
        F.load("F"+ ofToString(i) + ".jpg");
        P.load("P" + ofToString(i) + ".jpg");
        
        A.resize(w,h);
        F.resize(w, h);
        P.resize(w, h);
        
        A.update();
        F.update();
        P.update();
        
        _Amps.push_back(A);
        _Frqs.push_back(F);
        _Phzs.push_back(P);
    }

    _Font.load("vag.ttf",24);
}

//--------------------------------------------------------------
void ofApp::update(){
    float t = ofGetElapsedTimef();
    for(int i=0;i<_DynamicLine.size();i++)
    {
        ofVec2f pos = _BaseLine[i];
        ofVec2f normal = _DynamicLine.getNormalAtIndex(i);
        ofVec2f v_offset(0);
        for(int k=0;k<_Amps.size();k++)
        {
            float amp = 20.0f*_Amps[k].getColor(pos.x,pos.y).getBrightness();
            float freq = _Frqs[k].getColor(pos.x, pos.y).getBrightness() * 50.0f;
            float phaze = _Phzs[k].getColor(pos.x,pos.y).getBrightness() * 2.0f * PI;
            float offset = amp * sin(freq * t + phaze);
            v_offset += normal * offset;
        }
        ofVec2f posD = pos + v_offset;
        _DynamicLine[i] = posD;
    }
}

//--------------------------------------------------------------
void ofApp::draw(){
    ofPushStyle();
    ofNoFill();
    ofSetColor(0,0,0,80);
    _BaseLine.draw();
    ofPopStyle();
    
	if (_DynamicLine.size() > 0)
	{
		ofPushStyle();
		ofFill();
		ofSetColor(ofColor::white);
		ofBeginShape();
		for (int i = 0; i<_DynamicLine.size(); i++)
		{
			ofVec2f p = _DynamicLine[i];
			ofVertex(p.x, p.y);
		}
		ofEndShape();
		ofPopStyle();
	}
    
    
    ofPushStyle();
    ofNoFill();
    ofSetColor(0, 0, 0);
    _DynamicLine.draw();
    ofPopStyle();
    
    float t = ofGetElapsedTimef();
    ofPushStyle();
    
        float w,h;
        w = ofGetWidth();
        h = ofGetHeight();
        for(int i=10;i<w;i+=20)
        {
            for(int j=10;j<h;j+=20)
            {
                ofVec2f pos(i,j);
                for(int k=0;k<_Amps.size();k++)
                {
                    float amp = 5.0f*_Amps[k].getColor(i,j).getBrightness();
                    float freq = _Frqs[k].getColor(i,j).getBrightness() * 50.0f;
                    float phaze = _Phzs[k].getColor(i,j).getBrightness() * 2.0f * PI;
                    float offset = amp * sin(freq * t + phaze);
                    pos += ofVec2f(0,offset);
                }
                ofFill();
                ofSetColor(255,255,255,50);
                ofDrawCircle(pos,5);
                ofNoFill();
                ofSetColor(0,0,0,50);
                ofDrawCircle(pos,5);
            }
        }
    
    ofPopStyle();

    
    ofVec2f ctr =
        _DynamicLine.getCentroid2D();
    ofPushStyle();
    float txtwd = _Font.stringWidth(_Text);
    float txtht = _Font.stringHeight(_Text);
    ofRectangle R;
    R.setFromCenter(ctr.x, ctr.y, txtwd, txtht);
    ofSetColor(0);
    _Font.drawString(_Text, R.getLeft(), R.getBottom());
    ofPopStyle();
    
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    _Text += key;
    
    if(OF_KEY_F1==key)
    {
        _Text.clear();
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
    _BaseLine.addVertex(ofVec2f(x,y));
    _DynamicLine.addVertex(ofVec2f(x,y));
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
    _BaseLine.clear();
    _DynamicLine.clear();
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){
    _BaseLine.close();
    _DynamicLine.close();
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
