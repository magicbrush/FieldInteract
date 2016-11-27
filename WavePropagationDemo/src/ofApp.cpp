#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    screenW = ofGetWidth();
    screenH = ofGetHeight();
    
	// 障碍物
    _FCoef.allocate(screenW, screenH, OF_IMAGE_GRAYSCALE);
    _FCoef.load("Coef.jpg");
    _FCoef.resize(screenW,screenH);
    _FCoef.update();    
    
	// 波形初始状态
    _FWave.allocate(screenW, screenH, OF_IMAGE_GRAYSCALE);
    _FWave.load("Wave.jpg");
    _FWave.resize(screenW,screenH);
    _FWave.update();
    
	// 速度初始化为0
    _FSpd.allocate(screenW, screenH, OF_IMAGE_GRAYSCALE);
    _FSpd.setColor(ofFloatColor(0,0,0,0));
    _FSpd.update();
    
	// 显示效果初始化为0
    _FWaveDisp.allocate(screenW,screenH,OF_IMAGE_GRAYSCALE);
	_FWaveDisp.setColor(ofFloatColor(0.5f,0.5f,0.5f,1.0f));
	_FWaveDisp.update();
    
	// 控制参数
    _coef.set("Coef",0.8f,0.0f,5.0f);// 控制振动的传播快慢
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
    
	// 每个update()中可以让波形计算多次
	int updateCount = 1;
    for(int mm=0;mm<updateCount;mm++)
    {
		for(int i=0;i<screenW;i++)
		{
			for(int j=0;j<screenH;j++)
			{
				// 对每个像素i,j计算振动
				ofVec2f Coord(i,j);
				ofFloatColor W = _FWave.getColor(i,j);
				float w = W.getBrightness();
            
				// 这个像素会向着四个相邻像素的平均值移动
				// 四个相邻像素的坐标偏移量
				ofVec2f NB[4] = {ofVec2f(-1,0),ofVec2f(1,0),ofVec2f(0,-1),ofVec2f(0,1)};
				float deltaW = 0.0f; // 四个相邻像素与这个像素的差值
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
				
				// 变化的加速度正比于差值coef
				float acc = _coef*coef*deltaW / 4.0f;
				acc = ofClamp(acc, -10, 10);

				// 计算变化速度
				ofFloatColor CSpd = _FSpd.getColor(i, j);
				float spd = CSpd.getBrightness();
				spd = ofClamp(spd, -5, 5);				

				// 更新速度
				spd += acc*dt;
				spd = ofClamp(spd, -10, 10);
				_FSpd.setColor(i, j, ofFloatColor(spd, 1.0f));
            				
				// 更新波形
				w += spd*dt;
				w = ofClamp(w, -10, 10);
				_FWave.setColor(i, j, ofFloatColor(w,1.0f));
            
				// 更新波形显示效果：对波形进行尺度缩放和平移
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
    // 显示波形
    _FWaveDisp.draw(0,0,ofGetWidth(),ofGetHeight());
    
	// 显示界面
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
