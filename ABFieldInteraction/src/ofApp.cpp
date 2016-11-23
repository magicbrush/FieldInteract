#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    bool bA = _A.load("A.jpg");
    _A.resize(ofGetWidth(),ofGetHeight());
    
    bool bB = _B.load("B.jpg");
    _B.resize(ofGetWidth(),ofGetHeight());
    
    _spd = 200.0f;
    
}

//--------------------------------------------------------------
void ofApp::update(){
    float dt = ofGetLastFrameTime();
    
    for(int i=0;
        i<_A.getWidth();
        i++)
    {
        for(int j=0;
            j<_A.getHeight();
            j++)
        {
            ofVec2f A = getVec2fAt(i,j,_A);
            ofVec2f B = getVec2fAt(i,j,_B);
            
            float dATheta_dt = (B.x-B.y)*B.length();
            float dBTheta_dt = (A.y-A.x)*A.length();
            
            A = A.rotate(100.0f*dATheta_dt*dt);
            B = B.rotate(100.0f*dBTheta_dt*dt);
           
            setVec2fAt(i,j,A,_A);
            setVec2fAt(i,j,B,_B);
        }
    }
    _A.update();
    _B.update();
    
    for(int i=0;i<_PosV.size();i++)
    {
        ofVec2f vel = getVec2fInterpolateAt(_PosV[i], _A);
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

    
}

//--------------------------------------------------------------
void ofApp::draw(){

    float wd,ht;
    wd = ofGetWidth();
    ht = ofGetHeight();
    
    drawVecField(_A, ofColor(0,0,0,125));
    drawVecField(_B, ofColor(255,0,0,125));
    
    for(int i=0;i<_PosV.size();i++)
    {
        drawCircleFillColor(
             _PosV[i],10,ofColor(0,255,255,150));
        
        ofVec2f pos = _PosV[i];
        ofVec2f dir =
            getVec2fInterpolateAt(pos, _B);
        drawDirFillColor(
            pos,dir,5.0f,ofColor(0,255,0,150));
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

   }

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){
    _PosV.push_back(ofVec2f(x,y));
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

ofVec2f ofApp::getVec2fAt(int x, int y, ofFloatImage& Field)
{
    ofFloatColor c = Field.getColor(x,y);
    ofVec2f vec(c.r-0.5f,c.g-0.5f);
    return vec;
}

ofVec2f ofApp::getVec2fInterpolateAt(
            ofVec2f pos,ofFloatImage& Field)
{
    ofVec2f pos_lu(floor(pos.x),floor(pos.y));
    ofVec2f pos_ru(ceil(pos.x),floor(pos.y));
    ofVec2f pos_ld(floor(pos.x),ceil(pos.y));
    ofVec2f pos_rd(ceil(pos.x),ceil(pos.y));
    
    ofFloatColor clu = Field.getColor(pos_lu.x, pos_lu.y);
    ofFloatColor cru = Field.getColor(pos_ru.x, pos_ru.y);
    ofFloatColor cld = Field.getColor(pos_ld.x, pos_ld.y);
    ofFloatColor crd = Field.getColor(pos_rd.x, pos_rd.y);
    
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

void ofApp::setVec2fAt(
        int x, int y,
        ofVec2f Vec,ofFloatImage& Field)
{
    ofFloatColor cr(Vec.x+0.5f, Vec.y+0.5f,0.0f,1.0f);
    Field.setColor(x,y,cr);
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

void ofApp::drawDirFillColor(
                      ofVec2f pos,
                      ofVec2f dir,
                      float width,
                      ofColor cr)
{
    ofPushMatrix();
    ofTranslate(pos.x, pos.y);
    ofRotateZ(dir.angle(ofVec2f(1,0)));
    ofPushStyle();
    ofSetColor(cr);
    ofDrawRectangle(-width/2, -width/2, 5+60*dir.length(), width);
    ofSetColor(0);
    ofNoFill();
    ofDrawRectangle(-width/2, -width/2, 5+60*dir.length(), width);
    ofPopStyle();
    ofPopMatrix();
}


void ofApp::drawVecField(ofFloatImage& F, ofColor Cr)
{
    int wd,ht;
    wd = F.getWidth();
    ht = F.getHeight();
    ofPushStyle();
    ofSetColor(Cr);
    for(int i=0;i<=wd;i+=25)
    {
        for(int j=0;j<=ht;j+=25)
        {
            ofVec2f pos(i,j);
            ofVec2f vec = getVec2fInterpolateAt(pos,F);
            ofDrawArrow(pos-18.0f*vec,
                        pos+18.0f*vec,2.5f);
        }
    }
    ofPopStyle();
}

