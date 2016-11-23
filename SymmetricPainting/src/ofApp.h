#pragma once

#include "ofMain.h"

#include "ofxGui.h"
class SymmetricVelParticle;

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
    
    ofFbo _Canvas;
    
    vector<ofPtr<SymmetricVelParticle> > _pBrushes;
		
    ofxPanel _GUI;
    ofParameter<float> _DragSpd;
    ofParameter<bool> _bAddBrush;
    ofParameter<bool> _bRandomBrushProps;
    ofParameter<ofColor> _Color;
    ofParameter<float> _Rot;
    ofParameter<float> _Scale;
    ofParameter<float> _Radius;
    bool _bShowGUI;
};
