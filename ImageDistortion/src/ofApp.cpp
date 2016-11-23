#include "ofApp.h"
#include "utilities.h"
#include "DrawingParticle.hpp"
#include "FD_Rotation.hpp"

//--------------------------------------------------------------
void ofApp::setup(){
    
    ofSetFrameRate(60.0f);

	_ISource.load("Source.jpg");
	_ISource.resize(ofGetWidth(), ofGetHeight());
	_ISource.update();
	_IDistort.clone(_ISource);
	_IDistort.update();
	_DistortionAmt.set("DistortionAmt", 10.0f, 0.0f, 256.0f);
    
    ofFloatImage I;
    I.load("VField.jpg");
    
    _VField.allocate(ofGetWidth(),ofGetHeight(),GL_RGBA32F);
    _VField.begin();
    ofClear(0,0,0,0);
    I.draw(0,0,_VField.getWidth(),_VField.getHeight());
    _VField.end();
    
    _BrushImg.allocate(64,64,OF_IMAGE_COLOR_ALPHA);
    _BrushOn.set("BrushOn",true);
    _BrScale.set("Scale",1.0f,0.2f,5.0f);
    _BrCentric.set("Centric",1.0f,-10.0f,10.0f);
    _BrCentric.addListener(this,&ofApp::BrParamChange);
    _BrYXRatio.set("BrYXRatio",1.0f,-1.0f,1.0f);
    _BrYXRatio.addListener(this,&ofApp::BrParamChange);
    _BrRotation.set("Rotation",0.0f,-180.0f,180.0f);
    _BrRotation.addListener(this,&ofApp::BrParamChange);
    _BrStrength.set("Strength",0.3f,0.01f,1.0f);
    _BrStrength.addListener(this,&ofApp::BrParamChange);
    _BrBiasDir.set("BiasDir",0.0f,-180.0f,180.0f);
    _BrBiasDir.addListener(this,&ofApp::BrParamChange);
    _BrBiasStr.set("BiasStr",0.0f,-10.0f,10.0f);
    _BrBiasStr.addListener(this,&ofApp::BrParamChange);
    _BrRandomBias.set("RandomBias",0.0f,0.0f,10.0f);
    _BrRandomBias.addListener(this,&ofApp::BrParamChange);
    _BrPreview.set("Preview",true);
    _BrPreviewSize.set("BrushPreviewSize",140.0f,30.0f,320.0f);
    _BrushControl.setName("Brush");
    _BrushControl.add(_BrushOn);
    _BrushControl.add(_BrScale);
    _BrushControl.add(_BrCentric);
    _BrushControl.add(_BrYXRatio);
    _BrushControl.add(_BrRotation);
    _BrushControl.add(_BrStrength);
    _BrushControl.add(_BrBiasDir);
    _BrushControl.add(_BrBiasStr);
    _BrushControl.add(_BrRandomBias);
    _BrushControl.add(_BrPreview);
    _BrushControl.add(_BrPreviewSize);    
       
    _AddDynamic.set("AddDynamic",false);
    _DynamicType.set("DynamicType",0,0,1);
    _DynamicRadius.set("DynamicRadius",10.0f,5.0f,100.0f);
    _DynamicSpeed.set("DynamicSpeed",100.0f,0.0f,500.0f);
    _ClearDynamics.set("ClearDynamics",false);
    _Dynamics.setName("Dynamics");
    _Dynamics.add(_AddDynamic);
    _Dynamics.add(_DynamicType);
    _Dynamics.add(_DynamicRadius);
    _Dynamics.add(_DynamicSpeed);
    _Dynamics.add(_ClearDynamics);
    
    _bDrawVField.set("DrawVecField",true);
    _VecDispRes.set("VecFieldDisplayRes",20,10,50);
    _VecDispColor.set("VecDispColor",
        ofFloatColor(0,0,0,0.4f),
        ofFloatColor(0,0,0,0),
        ofFloatColor(1,1,1,1));
    _DisplayControl.setName("Display");
    _DisplayControl.add(_bDrawVField);
    _DisplayControl.add(_VecDispRes);
    _DisplayControl.add(_VecDispColor);
    
    GUI.setup();
    GUI.setName("Control Panel");
    //GUI.setShape(ofGetWidth()-200, 0, 200, 400);
    GUI.setSize(200, 400);
    GUI.setPosition(ofGetWidth()-200,0);
	GUI.add(_DistortionAmt);
    GUI.add(_BrushControl);    
    GUI.add(_Dynamics);
    GUI.add(_DisplayControl);
    bDrawGUI = true;
    
    screenw = ofGetWidth();
    screenh = ofGetHeight();
    
	updateBrushImg();
}

//--------------------------------------------------------------
void ofApp::update(){
    _VField.getTexture().readToPixels(_VFPx);
    
	int iw, ih;
	iw = _ISource.getWidth();
	ih = _ISource.getHeight();
	for (int i = 0; i < iw; i++)
	{
		for (int j = 0; j < ih; j++)
		{
			ofFloatColor cr = _VFPx.getColor(i, j);
			ofVec2f offset(cr.r - 0.5f, cr.g - 0.5f);
			offset *= _DistortionAmt;
			ofVec2f pos = ofVec2f(i, j) + offset;
			pos.x = ofWrap(pos.x,0, ofGetWidth());
			pos.y = ofWrap(pos.y,0, ofGetHeight());
			ofColor cr2 = _ISource.getColor(pos.x, pos.y);
			_IDistort.setColor(i, j, cr2);
		}
	}
	_IDistort.update();

    float dt = ofGetLastFrameTime();
    if(ofGetMousePressed() && _BrushOn)
    {
        //cout << "brushDraw:" << endl;
        BrushDrawToVecField();
    }    
    
    for(int i=0;i<_FDynamics.size();i++)
    {
        _FDynamics[i]->update(dt,_VFPx,_VField);
    }  

}

//--------------------------------------------------------------
void ofApp::draw(){   
    
	_IDistort.draw(0, 0, ofGetWidth(), ofGetHeight());

    if(_bDrawVField)
    {
        drawVField();
    }    
    
    for(int i=0;i<_FDynamics.size();i++)
    {
        _FDynamics[i]->draw();
    }
       
    if(_BrPreview)
    {
        drawBrushPreview();
    }
    
    if(_BrushOn)
    {
        drawBrushShape();
    }
    
    if(bDrawGUI)
        GUI.draw();

}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){
    if(OF_KEY_F1==key)
    {
        bDrawGUI = !bDrawGUI;
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

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){
    
    if(_AddDynamic)
    {
        ofPtr<FieldDynamics> newFD;
        if(_DynamicType.get()==0)
        {
            newFD.reset(new FD_Rotation(_DynamicRadius,ofVec2f(x,y),_DynamicSpeed));
        }
        else
        {
            
        }
        _FDynamics.push_back(newFD);
        
    }
}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){
    ofSetWindowShape(screenw, screenh);
}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}

void ofApp::BrParamChange(float &v)
{
    updateBrushImg();
}
void ofApp::drawBrushPreview()
{
    ofRectangle R(
        0,0,
        _BrPreviewSize,_BrPreviewSize);
    
    ofPushStyle();
    ofSetColor(255,255,255,255);
    ofDrawRectangle(R);
    ofNoFill();
    ofSetColor(0);
    ofDrawRectangle(R);
    ofPopStyle();
    
    ofRectangle R2 = R;
    R2.scaleFromCenter(0.8f);
    ofPushStyle();
    ofFloatColor Cr = _VecDispColor.get();
    Cr.a = _BrStrength.get();
    ofSetColor(Cr);
    ofFloatPixels& Px =
        _BrushImg.getPixels();
    utils::drawVecField(Px,
        R2,_VecDispRes/3.0f, 1.5f, true);
    ofPopStyle();
    
}
void ofApp::updateBrushImg()
{
    int w,h;
    w = _BrushImg.getWidth();
    h = _BrushImg.getHeight();
    for(int i=0;i<w;i++)
    {
        for(int j=0;j<h;j++)
        {
            ofVec2f fromCtr;
            fromCtr.x = float(i)/w;
            fromCtr.y = float(j)/h;
            fromCtr -= ofVec2f(0.5f,0.5f);
            fromCtr.y *= _BrYXRatio;
            fromCtr*=2.0f;
            float distToCtr = fromCtr.length();
            distToCtr = ofClamp(distToCtr,0,1);
            float decay = ofMap(distToCtr,0,1,1,0);
            
            ofVec2f fromCtrN = fromCtr.getNormalized();
            fromCtrN *= _BrCentric;
            fromCtrN.rotate(_BrRotation);
            ofVec2f bias(1,0);
            bias.rotate(_BrBiasDir);
            bias*=_BrBiasStr;
            fromCtrN += bias;
            
            ofVec2f randBias(1,0);
            randBias.rotate(ofRandom(-180,180));
            randBias *= _BrRandomBias;
            fromCtrN += randBias;
            
            float alpha = decay * _BrStrength;
            
            ofFloatColor cr(
                fromCtrN.x+0.5f,
                fromCtrN.y+0.5f,
                0.0f,
                alpha);
            
            _BrushImg.setColor(i,j,cr);
        }
    }
    _BrushImg.update();
}

void ofApp::BrushDrawToVecField()
{
    float dt = ofGetLastFrameTime();
    
    float bw,bh;
    bw = _BrushImg.getWidth();
    bh = _BrushImg.getHeight();
    _VField.begin();
    ofPushMatrix();
    ofTranslate(mouseX,mouseY,0.0f);
    //cout << "drawPos:" << ofVec2f(mouseY,mouseX) << endl;
    ofScale(_BrScale,_BrScale,1.0f);
    ofPushStyle();
    ofSetColor(255,255,255,dt*255);
    _BrushImg.draw(-bw/2,-bh/2,bw,bh);
    ofPopStyle();
    ofPopMatrix();
    _VField.end();
}
void ofApp::drawBrushShape()
{
    ofPushStyle();
    ofPushMatrix();
    ofTranslate(mouseX, mouseY,1.0f);
    ofScale(_BrScale/2.0f,_BrScale/2.0f,1.0f);
    ofNoFill();
    ofSetColor(0,0,0,100);
    ofDrawCircle(ofVec2f(0),_BrushImg.getWidth());
    ofPopMatrix();
    ofPopStyle();

}

void ofApp::clearDynamics(bool& bClear)
{
    if(bClear)
    {
        _ClearDynamics = false;
        _FDynamics.clear();
    }
}
void ofApp::drawVField()
{
    ofPushStyle();
    ofSetColor(_VecDispColor.get());
    
    utils::drawVecField(_VFPx,
          ofRectangle(0,0,ofGetWidth(),ofGetHeight()),_VecDispRes, 2.5f, false);
    ofPopStyle();
}


