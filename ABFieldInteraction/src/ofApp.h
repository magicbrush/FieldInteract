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
    
    ofVec2f getVec2fAt(
                int x, int y, ofFloatImage& Field);
    ofVec2f getVec2fInterpolateAt(
                ofVec2f pos, ofFloatImage& Field);
    void setVec2fAt(int x, int y, ofVec2f Vec, ofFloatImage& Field);
    
    void drawCircleFillColor(
            ofVec2f pos,
            float Radius=10.0f,
            ofColor cr=ofColor::green);
    void drawDirFillColor(
            ofVec2f pos,
            ofVec2f dir,
            float width=5.0f,
            ofColor cr=ofColor::green);
    void drawVecField(ofFloatImage& F, ofColor Cr);
    
    ofFloatImage _A,_B;
    
    std::vector<ofVec2f> _PosV;
    float _spd;

};
