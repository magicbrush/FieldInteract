#pragma once

#include "ofMain.h"

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
    
    ofPolyline _BaseLine; // 基准线
    ofPolyline _DynamicLine; // 动态线
    
    vector<ofFloatImage> _Amps; // 振幅
    vector<ofFloatImage> _Frqs; // 频率
    vector<ofFloatImage> _Phzs; // 相位
    
    ofTrueTypeFont _Font; // 字体
    string _Text; // 要显示的文本
};
