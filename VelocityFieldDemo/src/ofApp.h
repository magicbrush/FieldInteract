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
    
    // draw a circle
    void drawCircleFillColor(
            ofVec2f pos,
            float Radius=10.0f,
            ofColor cr=ofColor::green);
    // get ofFloatColor at (x,y)
    // then convert to ofVec2f
    ofVec2f getVec2fAt(int x, int y);
    // get interpolated ofVec2f
    ofVec2f getVec2fInterpolateAt(ofVec2f pos);
    
    // vector field: an Image
    ofFloatImage _VecField;
    
    // particles move along vectors
    std::vector<ofVec2f> _PosV;
    float _spd;

    // particle moving by accelleration
    std::vector<ofVec2f> _PosA;
    std::vector<ofVec2f> _VelA;
    float _acc;
    float _spd2;
        
    
};
