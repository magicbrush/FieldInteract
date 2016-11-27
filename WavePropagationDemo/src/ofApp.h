#pragma once

#include "ofMain.h"
#include "ofxGui.h"

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void mouseEntered(int x, int y);
		void mouseExited(int x, int y);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
    
	// 控制参数
	// _coef: 振动系数
    ofParameter<float> _coef;
	// 下面两个控制显示效果
    ofParameter<float> _dispOffset;
    ofParameter<float> _dispScale;
    ofParameterGroup _Control;
    ofxPanel _GUI;    
    
    ofFloatImage _FCoef; // 障碍物
    ofFloatImage _FWave; // 波动场（灰度值）
    ofFloatImage _FSpd; // 振动速度
    
    ofFloatImage _FWaveDisp; // 显示出来的图像
    
    int screenW,screenH; // 屏幕参数
		
};
