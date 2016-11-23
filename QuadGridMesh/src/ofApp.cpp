#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    
    ofDisableArbTex(); // to use uniform texture coordinates, this function must be called
    
    int ResX = 30;
    int ResY = 30;
    int id = 0;
    for(int i=0;i<ResX;i++)
    {
        for(int j=0;j<ResY;j++)
        {
            float x = i * ofGetWidth()/(ResX-1);
            float y = j * ofGetWidth()/(ResY-1);
            _Mesh.addVertex(ofPoint(x,y));
            _Mesh.addTexCoord(ofVec2f(x/ofGetWidth(),1.0f-y/ofGetWidth()));
            if(i>=1 && j>=1)
            {
                //_Mesh.addIndices(...)
                _Mesh.addTriangle(id, id-1, id-ResX-1);
                _Mesh.addTriangle(id, id-ResX, id-ResX-1);
            }
            id ++;
        }
    }
    
    _Img.loadImage("Tiger.jpg");
    _Img.getTexture().setTextureWrap(GL_MIRRORED_REPEAT, GL_MIRRORED_REPEAT);
    
    _bShowWireframe= true;
    
    _distortMode = STATIC;
    _mouseButton = -1;
}

//--------------------------------------------------------------
void ofApp::update(){
    float dt = ofGetLastFrameTime();
    
    if(_distortMode==STATIC)
    {
        for(int i=0;i<_Mesh.getNumTexCoords();i++)
        {
            ofVec2f texCoord = _Mesh.getTexCoordsPointer()[i];
            float x = texCoord.x * ofGetWidth();
            float y = ofGetHeight() - texCoord.y * ofGetHeight();
            _Mesh.setVertex(i, ofVec2f(x,y)) ;
        }
    }
    else if(_distortMode==TURBULANCE)
    {
        for(int i=0;i<_Mesh.getNumVertices();i++)
        {
            ofVec3f pt = _Mesh.getVertex(i);
            pt += ofVec2f(10.0f*ofRandom(-dt,dt),10.0f*ofRandom(-dt,dt));
            _Mesh.setVertex(i,pt);
        }
    }
    else if(_distortMode==WAVE)
    {
        float T = ofGetElapsedTimef();
        for(int i=0;i<_Mesh.getNumTexCoords();i++)
        {
            ofVec2f texCoord = _Mesh.getTexCoordsPointer()[i];
            float x = texCoord.x * ofGetWidth();
            float y = ofGetHeight() - texCoord.y * ofGetHeight();
            float dx = 5.0f*sin(1.92*T + 20.0f*texCoord.x);
            float dy = 5.0f*sin(2.5*T + 20.0f*texCoord.y);
            _Mesh.setVertex(i, ofVec2f(x+dx,y+dy)) ;
        }
    }
    else if(_distortMode==ZOOM)
    {
        ofVec2f Ctr(0.5f,0.5f);
        for(int i=0;i<_Mesh.getNumTexCoords();i++)
        {
            ofVec2f txCoord = _Mesh.getTexCoordsPointer()[i];
            
            ofVec2f Offset = txCoord-Ctr;
            ofVec2f Distort = -200.0f* Offset  * exp(-3.0f*Offset.length());
            
            float x = txCoord.x * ofGetWidth();
            float y = ofGetHeight() - txCoord.y * ofGetHeight();
            ofVec2f Pt(x,y);
            ofVec2f pos = Pt + Distort;
            _Mesh.setVertex(i,pos);
        }
    }
    else if(_distortMode==PINCH)
    {
        float x = ofGetMouseX();
        float y = ofGetMouseY();
        ofVec3f mousePos(x,y,0);
        
        for(int i=0;i<_Mesh.getNumVertices();i++)
        {
            ofVec3f vt = _Mesh.getVertex(i);
            ofVec3f offset = mousePos - vt;
            
            float dist = offset.length();
            float force = _mouseButton==0?exp(-0.1f*dist):0.0f;
            force *= 10.0f*dt;
            ofVec3f move = offset * force;
            _Mesh.setVertex(i, vt + move);
        }
        
    }
    else if(_distortMode==DILUTE)
    {
        float x = ofGetMouseX();
        float y = ofGetMouseY();
        ofVec3f mousePos(x,y,0);
        
        for(int i=0;i<_Mesh.getNumVertices();i++)
        {
            ofVec3f vt = _Mesh.getVertex(i);
            ofVec3f offset = mousePos - vt;
            
            float dist = offset.length();
            
            float force = _mouseButton==0?-exp(-0.1f*dist):0.0f;
            force *= 10.0f*dt;
            
            ofVec3f move = offset * force;
            _Mesh.setVertex(i, vt + move);
        }
        
    }
    else if(_distortMode==ROTATION)
    {
        float x = ofGetMouseX();
        float y = ofGetMouseY();
        ofVec3f mousePos(x,y,0);
        
        for(int i=0;i<_Mesh.getNumVertices();i++)
        {
            ofVec3f vt = _Mesh.getVertex(i);
            ofVec3f offset = mousePos - vt;
            
            float dist = offset.length();
            
            float force = _mouseButton==0?-exp(-0.01f*dist):0.0f;
            
            force *= 10.0f*dt;
            force = 0.5f;
            
            ofVec3f dir = offset;
            dir = dir.rotate(90.0f,ofVec3f(0,0,1));
            dir.normalize();
            
            ofVec3f move = dir * force;
            _Mesh.setVertex(i, vt + move);
        }
    }

}

//--------------------------------------------------------------
void ofApp::draw(){
    
    
    _Img.bind();
    _Mesh.drawFaces();
    _Img.unbind();
    
    if(_bShowWireframe)
    {
        ofPushStyle();
        ofSetColor(ofColor(255,255,255,55));
        _Mesh.drawWireframe();
        ofPopStyle();
    }

}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){
    
    if(key==OF_KEY_F1)
    {
        _bShowWireframe = !_bShowWireframe;
    }
    else if(key==OF_KEY_F2)
    {
        _distortMode = (DistortionMode)0;
    }
    else if(key==OF_KEY_F3)
    {
        _distortMode = (DistortionMode)1;
    }
    else if(key==OF_KEY_F4)
    {
        _distortMode = (DistortionMode)2;
    }
    else if(key==OF_KEY_F5)
    {
        _distortMode = (DistortionMode)3;
    }
    else if(key==OF_KEY_F6)
    {
        _distortMode = (DistortionMode)4;
        
    }
    else if(key==OF_KEY_F7)
    {
        _distortMode = (DistortionMode)5;
    }
    else if(key==OF_KEY_F8)
    {
        _distortMode = (DistortionMode)6;
    }
}


//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){
    _mouseButton = button;
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
    _mouseButton = button;
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){
    _mouseButton = -1;
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
