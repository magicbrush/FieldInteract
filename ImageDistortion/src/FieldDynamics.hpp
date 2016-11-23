//
//  FieldDynamics.hpp
//  VecFieldPainting
//
//  Created by Bentley on 16/11/19.
//
//

#ifndef FieldDynamics_hpp
#define FieldDynamics_hpp

#include <stdio.h>
#include "ofMain.h"

class FieldDynamics
{
public:
    FieldDynamics(ofVec2f pos, float radius);
    virtual void update(float dt, ofFloatPixels& VF, ofFbo& Field) = 0;
    virtual void draw();
    
protected:
    float getAffectStrength(ofVec2f _target);
    
    ofVec2f _pos;
    float _radius;
    
};

#endif /* FieldDynamics_hpp */
