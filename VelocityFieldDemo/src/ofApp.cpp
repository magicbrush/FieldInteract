#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    _VecField.load("VelField.jpg");
    _VecField.resize(ofGetWidth(),ofGetHeight());
    
    _PosV.push_back(
            ofVec2f(
                ofGetWidth()/2.0f,
                ofGetHours()/2.0f));
    _spd = 100.0f;
    
    _acc = 40.0f;
    _spd2 = 100.0f;
}

//--------------------------------------------------------------
void ofApp::update(){
    float dt = ofGetLastFrameTime();
    
    // rotate every vector in the
    // vector field
    for(int i=0;
        i<_VecField.getWidth();
        i++)
    {
        for(int j=0;
            j<_VecField.getHeight();
            j++)
        {
            ofFloatColor cr = _VecField.getColor(i, j);
            ofVec2f v(cr.r-0.5,cr.g-0.5);
            v.rotate(dt*20.0f);
            cr.r = v.x+0.5;
            cr.g = v.y+0.5;
            _VecField.setColor(i,j,cr);
        }
    }
    // after edit pixels in ofImage/ofFloatImage, we call update() to make it visible
    _VecField.update();
    
    // move every blue particles
    for(int i=0;i<_PosV.size();i++)
    {
        ofVec2f vel = getVec2fInterpolateAt(_PosV[i]);
        vel.limit(300.0f);
    
        ofVec2f movement = _spd*vel*dt;
    
        ofVec2f pos2 = _PosV[i] + movement;
        ofRectangle Rect(0,0,ofGetWidth(),ofGetHeight());
        if(!Rect.inside(pos2))
        {
            pos2.x = ofWrap(pos2.x,0,ofGetWidth());
            pos2.y = ofWrap(pos2.y,0,ofGetHeight());
        }
        _PosV[i] = pos2;
    }
    
    // move every pink particles
    for(int i=0;i<_PosA.size();i++)
    {
        ofVec2f acc = getVec2fInterpolateAt(_PosA[i]);
        
        ofVec2f deltaVel = _acc*acc*dt;
        
        ofVec2f vel2 = _VelA[i] + deltaVel;
        vel2.limit(3.0f);
        
        ofVec2f pos2 = _PosA[i] + vel2*_spd2*dt;
        
        ofRectangle Rect(0,0,ofGetWidth(),ofGetHeight());
        if(!Rect.inside(pos2))
        {
            pos2.x = ofWrap(pos2.x,0,ofGetWidth());
            pos2.y = ofWrap(pos2.y,0,ofGetHeight());
        }
        _VelA[i] = vel2;
        _PosA[i] = pos2;
    }
    
}

//--------------------------------------------------------------
void ofApp::draw(){
    
    
    float wd,ht;
    wd = ofGetWidth();
    ht = ofGetHeight();
    
    // draw the vector field as an image
    ofPushStyle();
    ofSetColor(255,120);
    _VecField.draw(0,0,wd,ht);
    ofPopStyle();
    
    // draw the vector as arrows
    ofPushStyle();
    ofSetColor(0);
    for(int i=0;i<=wd;i+=15)
    {
        for(int j=0;j<=ht;j+=15)
        {
            ofVec2f pos(i,j);
            ofVec2f vel = getVec2fInterpolateAt(pos);
            ofDrawArrow(pos-12.0f*vel,
                        pos+12.0f*vel,2.5f);
        }
    }
    ofPopStyle();
    
    // draw blue particles
    for(int i=0;i<_PosV.size();i++)
    {
        drawCircleFillColor(
            _PosV[i],10,ofColor(0,255,255,150));
    }
    
    // draw pink particles
    for(int i=0;i<_PosA.size();i++)
    {
        drawCircleFillColor(
            _PosA[i],6,ofColor(255,0,255,150));
    }
    
    

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

    if(ofRandom(0.0f,1.0f)<0.5f)
    {
        _PosV.push_back(ofVec2f(x,y));
    }
    else
    {
        _PosA.push_back(ofVec2f(x,y));
        _VelA.push_back(ofVec2f(0));
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

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}

ofVec2f ofApp::getVec2fAt(int x, int y)
{
    ofFloatColor c = _VecField.getColor(x,y);
    ofVec2f vec(c.r-0.5f,c.g-0.5f);
    return vec;
}

ofVec2f ofApp::getVec2fInterpolateAt(ofVec2f pos)
{
    // get four neighboring positions
    ofVec2f pos_lu(floor(pos.x),floor(pos.y));
    ofVec2f pos_ru(ceil(pos.x),floor(pos.y));
    ofVec2f pos_ld(floor(pos.x),ceil(pos.y));
    ofVec2f pos_rd(ceil(pos.x),ceil(pos.y));
    
    ofFloatColor clu = _VecField.getColor(pos_lu.x, pos_lu.y);
    ofFloatColor cru = _VecField.getColor(pos_ru.x, pos_ru.y);
    ofFloatColor cld = _VecField.getColor(pos_ld.x, pos_ld.y);
    ofFloatColor crd = _VecField.getColor(pos_rd.x, pos_rd.y);
    
    ofVec2f vlu(clu.r-0.5,clu.g-0.5);
    ofVec2f vru(cru.r-0.5f,cru.g-0.5f);
    ofVec2f vld(cld.r-0.5f,cld.g-0.5f);
    ofVec2f vrd(crd.r-0.5f,crd.g-0.5f);
    
    float a = pos.x - floor(pos.x);
    float b = pos.y - floor(pos.y);
    ofVec2f vl = b*vld + (1.0f-b)*vld;
    ofVec2f vr = b*vrd + (1.0f-b)*vrd;
    
    ofVec2f v = a*vr + (1.0f-a)*vl;
    
    return v;
}

void ofApp::drawCircleFillColor(
                         ofVec2f pos,
                         float Radius,
                         ofColor cr)
{
    ofPushStyle();
    ofSetColor(cr);
    ofDrawCircle(pos,Radius);
    ofNoFill();
    ofSetLineWidth(1.0f);
    ofSetColor(0);
    ofDrawCircle(pos,Radius);
    ofPopStyle();
}

