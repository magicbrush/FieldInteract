#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    _VecField.load("VelField.jpg");
    _VecField.resize(ofGetWidth(),ofGetHeight());
    _AffectSum.allocate(
        _VecField.getWidth(),
        _VecField.getHeight(),
        OF_IMAGE_COLOR);
    _spd = 100.0f;

}

//--------------------------------------------------------------
void ofApp::update(){
    float dt = ofGetLastFrameTime();
    
    _AffectSum.setColor(ofFloatColor(0.5f,0.5f,0));
    _AffectSum.update();
    
    // change vector field by every affector
    for(int i=0;i<_PosA.size();i++)
    {
        ofVec2f pos = _PosA[i];
        pos.x = int(pos.x);
        pos.y = int(pos.y);
        ofVec2f af = _Affects[i];
        
        for(int m=-1;m<=1;m++)
        {
            for(int n=-1;n<=1;n++)
            {
                if(m==0&&n==0)continue;
                int col = pos.x + m;
                int row = pos.y + n;
                col = ofWrap(col,0,_VecField.getWidth());
                row = ofWrap(row,0,_VecField.getHeight());
                
                ofVec2f pos2(col,row);
                ofVec2f offset = pos2-pos;
                
                ofVec2f Vec = offset;
                Vec.rotate(af.x);
                Vec.normalize();
                Vec *= af.y / offset.length();
                addVecAt(Vec, col, row, _AffectSum);
            }
        }
    }
    _AffectSum.update();
    
    // Add AffectSum to VecField
    // every pixel get average value of
    // its neighborhood
    for(int i=0;
        i<_VecField.getWidth();
        i++)
    {
        for(int j=0;
            j<_VecField.getHeight();
            j++)
        {
            ofVec2f deltaV = getVec2fAt(i,j,_AffectSum);
            
            ofVec2f p[5] = {ofVec2f(i,j),
                ofVec2f(i-1,j),ofVec2f(i+1,j),
                ofVec2f(i,j-1),ofVec2f(i,j+1)};
            ofVec2f sumVec(0);
            for(int n=0;n<5;n++)
            {
                int col = ofWrap(p[n].x,0,_VecField.getWidth());
                int row = ofWrap(p[n].y,0,_VecField.getHeight());
                ofVec2f vec = getVec2fAt(col, row, _VecField);
                sumVec += vec;
            }
            sumVec /= 5.0f;
            sumVec += deltaV;
            setVecAt(sumVec, i, j, _VecField);
        }
    }
    _VecField.update();
    
    
    // moving particles
    for(int i=0;i<_Pts.size();i++)
    {
        ofVec2f p = _Pts[i];
        ofVec2f vel = _spd * getVec2fInterpolateAt(p, _VecField);
        vel.limit(200.0f);
        p += vel * dt;
        ofRectangle Rect(0,0,ofGetWidth(),ofGetHeight());
        if(!Rect.inside(p))
        {
            p.x = ofWrap(p.x,0,ofGetWidth());
            p.y = ofWrap(p.y,0,ofGetHeight());
        }
        _Pts[i] = p;
    }
    
}

//--------------------------------------------------------------
void ofApp::draw(){
    
    float wd,ht;
    wd = ofGetWidth();
    ht = ofGetHeight();
    
    ofPushStyle();
    ofSetColor(255,120);
    _VecField.draw(0,0,wd,ht);
    ofPopStyle();
    
    ofPushStyle();
    ofSetColor(0);
    for(int i=0;i<=wd;i+=15)
    {
        for(int j=0;j<=ht;j+=15)
        {
            ofVec2f pos(i,j);
            ofVec2f vel = getVec2fInterpolateAt(pos,_VecField);
            vel.limit(1.5f);
            ofDrawArrow(pos-12.0f*vel,
                        pos+12.0f*vel,2.5f);
        }
    }
    ofPopStyle();
    
    for(int i=0;i<_PosA.size();i++)
    {
        drawCircleFillColor(
            _PosA[i],3,ofColor(0,255,255,20));
    }
    
    for(int i=0;i<_Pts.size();i++)
    {
        ofVec2f p = _Pts[i];
        drawCircleFillColor(p,12.0f,ofColor(0,255,0,100));
    }

}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){
    if(OF_KEY_F1)
    {
        float x = ofRandomWidth();
        float y = ofRandomHeight();
        _PosA.push_back(ofVec2f(x,y));
        // _PosV.push_back(ofVec2f(x,y));
        float rot = ofRandom(-180.0f,180.0f);
        float str = ofRandom(1.0f,20.0f);
        _Affects.push_back(ofVec2f(rot,str));
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
    _Pts.push_back(ofVec2f(x,y));
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

ofVec2f ofApp::getVec2fAt(int x, int y,ofFloatImage& F)
{
    ofFloatColor c = F.getColor(x,y);
    ofVec2f vec(c.r-0.5f,c.g-0.5f);
    return vec;
}

ofVec2f ofApp::getVec2fInterpolateAt(ofVec2f pos,ofFloatImage& F)
{
    ofVec2f pos_lu(floor(pos.x),floor(pos.y));
    ofVec2f pos_ru(ceil(pos.x),floor(pos.y));
    ofVec2f pos_ld(floor(pos.x),ceil(pos.y));
    ofVec2f pos_rd(ceil(pos.x),ceil(pos.y));
    
    ofFloatColor clu = F.getColor(pos_lu.x, pos_lu.y);
    ofFloatColor cru = F.getColor(pos_ru.x, pos_ru.y);
    ofFloatColor cld = F.getColor(pos_ld.x, pos_ld.y);
    ofFloatColor crd = F.getColor(pos_rd.x, pos_rd.y);
    
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

void ofApp::setVecAt(ofVec2f v,int x, int y,
        ofFloatImage& F, bool bUpdate)
{
    ofFloatColor cr(v.x+0.5f,v.y+0.5f,0.0f);
    F.setColor(x, y, cr);
    if(bUpdate)
    {
        F.update();
    }
}
void ofApp::addVecAt(
    ofVec2f v, int x, int y,
    ofFloatImage& F, bool bUpdate)
{
    ofVec2f vec = getVec2fAt(x,y,F);
    vec += v;
    setVecAt(vec,x,y,F,bUpdate);
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

