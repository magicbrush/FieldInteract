//
//  SymmetricVecParticle.hpp
//  SymmetricPainting
//
//  Created by Bentley on 16/11/20.
//
//

#ifndef SymmetricVelParticle_hpp
#define SymmetricVelParticle_hpp

#include <stdio.h>
#include "ofMain.h"

class SymmetricVelParticle
{
public:
    SymmetricVelParticle(ofColor color, float radius, ofVec2f pos, ofVec2f vel=ofVec2f(0));
    SymmetricVelParticle(float radius, ofVec2f pos, ofVec2f vel,
                         SymmetricVelParticle * parent = 0,
                         float rotation = ofRandom(-180,180),
                         float scale = ofRandom(0.3,3),
                         ofColor color= ofColor::black);
    void update(float dt);
    void draw();
    
    ofVec2f getVel();
    void setVel(ofVec2f v);
    ofVec2f getPos();
    void setPos(ofVec2f p);
    
private:
    void init(float radius,
              ofVec2f pos,
              ofVec2f vel,
              SymmetricVelParticle * parent,
              float rotation,
              float scale,
              ofColor color);
    void makeSymmetricVelToParent(ofVec2f parentVel);
    
    
    
private:
    SymmetricVelParticle * _ptrParent;
    float _Rot;
    float _Scale;
    
    float _Radius;
    ofVec2f _Pos;
    ofVec2f _Vel;
    
    ofColor _color;
};

#endif /* SymmetricVecParticle_hpp */
