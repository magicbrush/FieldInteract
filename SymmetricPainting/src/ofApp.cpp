#include "ofApp.h"
#include "SymmetricVelParticle.hpp"

//--------------------------------------------------------------
void ofApp::setup(){
    _Canvas.allocate(ofGetWidth(),ofGetHeight(),GL_RGBA);
    _Canvas.begin();
    ofClear(ofColor::white);
    _Canvas.end();
    
    ofPtr<SymmetricVelParticle> _br;
    _br.reset(new SymmetricVelParticle(
        7.0f,ofVec2f(ofGetWidth()/2,ofGetHeight()/2),
        ofVec2f(0),0,0,1,ofColor(0,0,0,255)));
    _pBrushes.push_back(_br);
    
    _GUI.setup("_GUI");
    _GUI.setPosition(0,0);
    _GUI.setSize(200,500);
    
    _DragSpd.set("DragSpeed",5.0f,0.5f,20.0f);
    _bAddBrush.set("AddBrush",false);
    _bRandomBrushProps.set("RandomBrushProps",true);
    _Color.set("Color",ofColor::black,ofColor(0,0,0,0),ofColor::white);
    _Rot.set("Rotation",0,-180,180);
    _Scale.set("Scale",1,-5.0f,5.0f);
    _Radius.set("Radius",6.0f,1.0f,20.0f);
    
    _GUI.add(_DragSpd);
    _GUI.add(_bAddBrush);
    _GUI.add(_bRandomBrushProps);
    _GUI.add(_Color);
    _GUI.add(_Rot);
    _GUI.add(_Scale);
    _GUI.add(_Radius);
    _bShowGUI = true;
    
    ofEnableAlphaBlending();
}

//--------------------------------------------------------------
void ofApp::update(){
    float dt = ofGetLastFrameTime();
    
    // update brushes
    for(int i=0;i<_pBrushes.size();i++)
    {
        _pBrushes[i]->update(dt);
        ofVec2f pos =_pBrushes[i]->getPos();
        ofRectangle R(0,0,ofGetWidth(),ofGetHeight());
        if(!R.inside(pos))
        {
            pos.x = ofWrap(pos.x,0,ofGetWidth());
            pos.y = ofWrap(pos.y,0,ofGetHeight());
            _pBrushes[i]->setPos(pos);
        }
    }
    
    // draw to canvas
    _Canvas.begin();
    for(int i=0;i<_pBrushes.size();i++)
    {
        _pBrushes[i]->draw();
    }
    _Canvas.end();

    // user control the 1st brush
    if(ofGetMousePressed() && !_bAddBrush)
    {
        ofVec2f mpos = ofVec2f(mouseX,mouseY);
        ofVec2f brPos =_pBrushes[0]->getPos();
        
        ofVec2f offset = mpos - brPos;
        ofVec2f vel = offset * _DragSpd;
        _pBrushes[0]->setVel(vel);
    }

}

//--------------------------------------------------------------
void ofApp::draw(){
    _Canvas.draw(0,0,ofGetWidth(),ofGetHeight());
    
    
    for(int i=0;i<_pBrushes.size();i++)
    {
        _pBrushes[i]->draw();
    }
    
    if(_bShowGUI)
    {
        _GUI.draw();
    }
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){
    if(OF_KEY_F1==key)
    {
        _bShowGUI= !_bShowGUI;
    }
}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
    
    if(_bAddBrush)
    {
        float radius = _Radius;
        float rot = _Rot;
        float scl = _Scale;
        ofColor color = _Color;
        if(_bRandomBrushProps)
        {
            radius = ofRandom(3,15);
            rot = ofRandom(-180,180);
            scl = ofRandom(-2,2);
            color = ofColor(
                ofRandom(255),ofRandom(255),
                ofRandom(255),ofRandom(75,150));
        }
        
        ofPtr<SymmetricVelParticle> newBr;
        newBr.reset(new SymmetricVelParticle(
            radius,
            ofVec2f(x,y),
            ofVec2f(0),
            _pBrushes[0].get(),
            rot,scl,color));
        _pBrushes.push_back(newBr);
    }
    else
    {
        _pBrushes[0]->setPos(ofVec2f(x,y));
    }
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
    ofSetWindowShape(_Canvas.getWidth(), _Canvas.getHeight());
}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
