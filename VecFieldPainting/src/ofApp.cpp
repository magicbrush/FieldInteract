#include "ofApp.h"
#include "utilities.h"
#include "DrawingParticle.hpp"
#include "FD_Rotation.hpp"

//--------------------------------------------------------------
void ofApp::setup(){
     // 限制帧率最大60帧/秒
    ofSetFrameRate(60.0f);
    
	// 设定矢量场的初始状态
    ofFloatImage I;
    I.load("VField.jpg");    
    _VField.allocate(ofGetWidth(),ofGetHeight(),GL_RGBA32F);
    _VField.begin();
    ofClear(0,0,0,0);
    I.draw(0,0,_VField.getWidth(),_VField.getHeight());
    _VField.end();
    
	// 彩色画布初始化
    _Canvas.allocate(ofGetWidth(),ofGetHeight(),GL_RGBA);
    _Canvas.begin();
    ofClear(255,255,255,255);
    _Canvas.end();
    
	// 初始化笔刷相关内容
	// 初始化笔刷图像
    _BrushImg.allocate(64,64,OF_IMAGE_COLOR_ALPHA);
	// 初始化笔刷参数
    _BrushOn.set("BrushOn",true);
    _BrScale.set("Scale",1.0f,0.2f,5.0f);
    _BrCentric.set("Centric",1.0f,-10.0f,10.0f);
	// 为这个参数添加回调函数
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
	// 上述参数都加入参数组，之后再将参数组加入图形界面
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
	// 更新笔刷内容
	updateBrushImg();
    
	// 移动粒子相关内容初始化
    _AddParticle.set("AddingParticles",false);
    _Radius.set("Radius",10.0f,3.0f,50.0f);
    _Color.set("Color",ofColor(255,0,0,50),ofColor(0,0,0,0),ofColor(255,255,255,255));
    _Speed.set("Speed",100.0f,0.0f,500.0f);
    _ClearParticles.set("Clear",false);
    _ClearParticles.addListener(this,&ofApp::clearParticles);
    _ParticleControl.setName("Particles");
    _ParticleControl.add(_AddParticle);
    _ParticleControl.add(_Radius);
    _ParticleControl.add(_Color);
    _ParticleControl.add(_Speed);
    _ParticleControl.add(_ClearParticles);
    
	// 矢量场动态化处理的相关内容初始化
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
    
	// 矢量场显示效果初始化
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
    
	// 图形界面初始化
    GUI.setup();
    GUI.setName("Control Panel");
    //GUI.setShape(ofGetWidth()-200, 0, 200, 400);
    GUI.setSize(200, 400);
    GUI.setPosition(ofGetWidth()-200,0);
    GUI.add(_BrushControl);
    GUI.add(_ParticleControl);
    GUI.add(_Dynamics);
    GUI.add(_DisplayControl);
    bDrawGUI = true;
    
    screenw = ofGetWidth();
    screenh = ofGetHeight();
}

//--------------------------------------------------------------
void ofApp::update(){
	// 将矢量场_VField的内容逐个像素的读取到_VFPx中
    _VField.getTexture().readToPixels(_VFPx);
    
    float dt = ofGetLastFrameTime();
    
	// 笔刷绘制到矢量场
	if(ofGetMousePressed() && _BrushOn)
    {
        //cout << "brushDraw:" << endl;
        BrushDrawToVecField();
    }
    
    // 矢量场动态处理
    for(int i=0;i<_FDynamics.size();i++)
    {
        _FDynamics[i]->update(dt,_VFPx,_VField);
    }
    
	// 粒子移动
    for(int i=0;i<_Particles.size();i++)
    {
        _Particles[i]->updatePosition(dt,_VFPx);
    }

	// 粒子绘制到画布
	_Canvas.begin();
	for (int i = 0; i<_Particles.size(); i++)
	{
		_Particles[i]->draw();
	}
	_Canvas.end();
    

}

//--------------------------------------------------------------
void ofApp::draw(){   

	// 显示画布
	_Canvas.draw(0, 0, ofGetWidth(), ofGetHeight());
    
	// 显示矢量场
    if(_bDrawVField)
    {
        drawVField();
    }
    
    // 显示动态化处理
    for(int i=0;i<_FDynamics.size();i++)
    {
        _FDynamics[i]->draw();
    }
    
    // 显示粒子
    drawParticles(true);
    
	// 显示笔刷预览
    if(_BrPreview)
    {
        drawBrushPreview();
    }
    
	// 显示笔刷形状
    if(_BrushOn)
    {
        drawBrushShape();
    }
    
	// 显示界面
    if(bDrawGUI)
        GUI.draw();

}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

	// F1切换界面的显示
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

	// 添加粒子或矢量场动态化处理源
    if(_AddParticle)
    {
        ofPtr<DrawingParticle> newPt;
        newPt.reset(new DrawingParticle(_Radius,_Color,ofVec2f(x,y),_Speed));
        _Particles.push_back(newPt);
    }
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

// 再左上角显示笔刷预览图像
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

// 按笔刷参数，更新笔刷内容
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

// 笔刷内容绘制到矢量场
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

// 显示笔刷形状
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

// 显示所有粒子
void ofApp::drawParticles(bool bVisualAid)
{
    for(int i=0;i<_Particles.size();i++)
    {
        ofPtr<DrawingParticle> ptrPt = _Particles[i];
        ptrPt->draw();
        if(bVisualAid)
        {
            ptrPt->drawVisualAids();
        }
    }
}

// 清空所有粒子
void ofApp::clearParticles(bool& bClear)
{
    if(bClear)
    {
        _ClearParticles = false;
        _ParticleControl.clear();
    }
}

// 清空动态化场
void ofApp::clearDynamics(bool& bClear)
{
    if(bClear)
    {
        _ClearDynamics = false;
        _FDynamics.clear();
    }
}

// 画出矢量场
void ofApp::drawVField()
{
    ofPushStyle();
    ofSetColor(_VecDispColor.get());
    
    utils::drawVecField(_VFPx,
          ofRectangle(0,0,ofGetWidth(),ofGetHeight()),_VecDispRes, 2.5f, false);
    ofPopStyle();
}


