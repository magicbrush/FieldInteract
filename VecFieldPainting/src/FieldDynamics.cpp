//
//  FieldDynamics.cpp
//  VecFieldPainting
//
//  Created by Bentley on 16/11/19.
//
//

#include "FieldDynamics.hpp"


FieldDynamics::FieldDynamics(ofVec2f pos, float radius):
_radius(radius),
_pos(pos)
{
    
}

float FieldDynamics::getAffectStrength(ofVec2f _target)
{
    ofVec2f offset = _target-_pos;
    float dist = offset.length();
    float affect = ofMap(dist,0,_radius,1.0f,0.0f,true);
    return affect;
}

void FieldDynamics::draw()
{
    ofPushStyle();
    ofSetColor(0,0,0,20);
    ofDrawCircle(_pos, _radius);
    ofPopStyle();
}
