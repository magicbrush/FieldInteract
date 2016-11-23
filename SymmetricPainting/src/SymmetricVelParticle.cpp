//
//  SymmetricVecParticle.cpp
//  SymmetricPainting
//
//  Created by Bentley on 16/11/20.
//
//

#include "SymmetricVelParticle.hpp"

SymmetricVelParticle::SymmetricVelParticle(
    ofColor color,float radius, ofVec2f pos, ofVec2f vel)
{
    init(radius,pos,vel,0,0,1,color);
}
SymmetricVelParticle::SymmetricVelParticle(
    float radius, ofVec2f pos, ofVec2f vel,
    SymmetricVelParticle * parent,
    float rotation,
    float scale,
    ofColor color)
{
    init(radius,pos,vel,
        parent,rotation,
         scale,color);
}

void SymmetricVelParticle::update(float dt)
{
    if(_ptrParent!=0)
    {
        ofVec2f vel =_ptrParent->getVel();
        //cout << "vel:" << vel<< endl;
        makeSymmetricVelToParent(vel);
    }
    
    _Pos += dt * _Vel;
    _Vel *= 0.98f;
}

void SymmetricVelParticle::draw()
{
    ofPushStyle();
    ofSetColor(_color);
    ofDrawCircle(_Pos,_Radius);
    ofPopStyle();
}

void SymmetricVelParticle::makeSymmetricVelToParent(
        ofVec2f parentVel)
{
    ofVec2f newVel = parentVel;
    newVel.rotate(_Rot);
    newVel *= _Scale;
    _Vel = newVel;
}

ofVec2f SymmetricVelParticle::getVel()
{
    return _Vel;
}

void SymmetricVelParticle::setVel(ofVec2f v)
{
    _Vel = v;
}

ofVec2f SymmetricVelParticle::getPos()
{
    return _Pos;
}
void SymmetricVelParticle::setPos(ofVec2f p)
{
    _Pos = p;
}

void SymmetricVelParticle::init(float radius,
          ofVec2f pos,
          ofVec2f vel,
          SymmetricVelParticle * parent,
          float rotation,
          float scale,
          ofColor color)
{
    _Radius=radius;
    _Pos=pos;
    _Vel=vel;
    _ptrParent=parent;
    _Rot=rotation;
    _Scale=scale;
    _color = color;
    
}
