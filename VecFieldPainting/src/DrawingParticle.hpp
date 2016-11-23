//
//  DrawingParticle.hpp
//  VecFieldPainting
//
//  Created by Bentley on 16/11/19.
//
//

#ifndef DrawingParticle_hpp
#define DrawingParticle_hpp

#include <stdio.h>
#include "ofMain.h"


class DrawingParticle
{
public:
    DrawingParticle(
        float radius=10.0f,
        ofColor cr= ofColor::green,
        ofVec2f pos = ofVec2f(0,0),
                    float spd=100.0f,
        float wrapProb = 0.03f);
    
    void updatePosition(float dt, ofFloatPixels& VecField);
    void draw();
    void drawVisualAids();
    
private:
    float _radius;
    ofColor _color;
    ofVec2f _pos;
    float _speed;
    float _wrapProb;
    
};

#endif /* DrawingParticle_hpp */
