#pragma once

#include "ofMain.h"
#include "ofxGui.h"

class DrawingParticle;
class FieldDynamics;
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
    
    ofFbo _VField;
    ofFloatPixels _VFPx;
    ofFbo _Canvas;
    
    ofFloatImage _BrushImg;
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
    ofParameterGroup _BrushControl;
    void BrParamChange(float &v);
    void drawBrushPreview();
    void updateBrushImg();
    void BrushDrawToVecField();
    void drawBrushShape();
    
    vector<ofPtr<DrawingParticle> > _Particles;
    ofParameter<bool> _AddParticle;
    ofParameter<float> _Radius;
    ofParameter<ofColor> _Color;
    ofParameter<float> _Speed;
    ofParameter<bool> _ClearParticles;
    ofParameterGroup _ParticleControl;
    void drawParticles(bool bVisualAid=false);
    void clearParticles(bool& bClear);
    
    vector<ofPtr<FieldDynamics> > _FDynamics;
    ofParameter<bool> _AddDynamic;
    ofParameter<int> _DynamicType;
    ofParameter<float> _DynamicRadius;
    ofParameter<float> _DynamicSpeed;
    ofParameter<bool> _ClearDynamics;
    void clearDynamics(bool& bClear);
    ofParameterGroup _Dynamics;
    
    ofParameter<bool> _bDrawVField;
    ofParameter<int> _VecDispRes;
    ofParameter<ofFloatColor> _VecDispColor;
    ofParameterGroup _DisplayControl;
    void drawVField();
    
    bool bDrawGUI;
    ofxPanel GUI;
    
    int screenw,screenh;

};
