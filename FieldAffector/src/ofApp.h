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
    
    void drawCircleFillColor(
            ofVec2f pos,
            float Radius=10.0f,
            ofColor cr=ofColor::green);
    
    ofVec2f getVec2fAt(int x, int y, ofFloatImage& F);
    ofVec2f getVec2fInterpolateAt(ofVec2f pos, ofFloatImage& F);
    void setVecAt(ofVec2f v, int x, int y,
                  ofFloatImage& F, bool bUpdate = false);
    void addVecAt(ofVec2f v, int x, int y,
                  ofFloatImage& F, bool bUpdate = false);
    // vector field
    ofFloatImage _VecField;
    
    // affection from affectors
    ofFloatImage _AffectSum;
    
    // affectors
    std::vector<ofVec2f> _PosA;
    std::vector<ofVec2f> _Affects;
    
    // moving particles
    std::vector<ofVec2f> _Pts;
    float _spd;
    
};
