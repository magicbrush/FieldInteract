#pragma once

#include "ofMain.h"
// 要用到图形界面，引用插件ofxGui
#include "ofxGui.h"

// 需要用到下面两个类：
class DrawingParticle;
class FieldDynamics;

// 主程序的定义
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
    
	//_VField： 矢量场：
		//用ofFbo来定义矢量场
		// 好处：便于对其进行编辑
		// 坏处：不便于访问到各个像素的数值
    ofFbo _VField;
	// _VFPx: 从_VField中逐像素获取数值
    ofFloatPixels _VFPx;
    // _Canvas：色彩场，所有运动粒子绘制的对象
	ofFbo _Canvas;
    
	// 笔刷
	// _BrushImg: 笔刷定义为一幅图像，用于向矢量场_VField绘制
    ofFloatImage _BrushImg; 
	// 下面一系列都是控制笔刷的参数，并显示在图形界面上
    ofParameter<bool> _BrushOn;
    ofParameter<float> _BrScale;
    ofParameter<float> _BrCentric;
    ofParameter<float> _BrYXRatio;
    ofParameter<float> _BrRotation;
    ofParameter<float> _BrStrength;
    ofParameter<float> _BrBiasDir;
    ofParameter<float> _BrBiasStr;
    ofParameter<float> _BrRandomBias;
    ofParameter<bool> _BrPreview;
    ofParameter<float> _BrPreviewSize;
	// 上述笔刷参数都放在参数组_BrushControl里
    ofParameterGroup _BrushControl;
	// BrParamChange(float &v)：上述笔刷参数的回调函数，
	// 当它们的数值改变时，将会调用这个函数
    void BrParamChange(float &v);
	// drawBrushPreview()： 绘制笔刷的预览图
    void drawBrushPreview();
	// updateBrushImg()：若上述笔刷参数改变，则更新笔刷图像
    void updateBrushImg();
	// BrushDrawToVecField(): 笔刷图向矢量场_VField绘制
    void BrushDrawToVecField();
	// drawBrushShape()：在屏幕上绘制笔刷形状，即显示一个空心圆圈
    void drawBrushShape();
    
	// 运动粒子：随着矢量场_VField运动，且向画布_Canvas绘制
	// 用容器vector保存数量可变的粒子对象
	// 粒子对象用智能指针来定义
    vector<ofPtr<DrawingParticle> > _Particles;
	// 下面一系列都是用于生成运动粒子的参数
	// _AddParticle：是否添加粒子，若为真，则点击屏幕就添加一个粒子
    ofParameter<bool> _AddParticle; 
	// 下列三项分别为创建新粒子的属性
    ofParameter<float> _Radius;
    ofParameter<ofColor> _Color;
    ofParameter<float> _Speed;
	// 清理粒子标记和回调函数
    ofParameter<bool> _ClearParticles;	
	void clearParticles(bool& bClear);
	// 上述运动粒子的参数都放在参数组_ParticleControl里
    ofParameterGroup _ParticleControl;
	// 显示所有运动粒子
    void drawParticles(bool bVisualAid=false);	
    
	// 一系列矢量场动态源
    vector<ofPtr<FieldDynamics> > _FDynamics;
	// 控制创建和消除矢量场动态源的参数
    ofParameter<bool> _AddDynamic;
    ofParameter<int> _DynamicType;
    ofParameter<float> _DynamicRadius;
    ofParameter<float> _DynamicSpeed;
	// 清除动态源的标记和回调函数
    ofParameter<bool> _ClearDynamics;
    void clearDynamics(bool& bClear);
	// 动态源的所有参数都放在参数组_Dynamics中
    ofParameterGroup _Dynamics;
    
	// 矢量场的显示效果控制
    ofParameter<bool> _bDrawVField;
    ofParameter<int> _VecDispRes;
    ofParameter<ofFloatColor> _VecDispColor;
    ofParameterGroup _DisplayControl;
    void drawVField();
    
    bool bDrawGUI;// 是否显示图形界面，用按键f1控制
    ofxPanel GUI; // 图形界面
    
	// 窗口尺寸
    int screenw,screenh;

};
