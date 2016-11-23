//
//  FD_Rotation.hpp
//  VecFieldPainting
//
//  Created by Bentley on 16/11/19.
//
//

#ifndef FD_Rotation_hpp
#define FD_Rotation_hpp

#include <stdio.h>
#include "FieldDynamics.hpp"

class FD_Rotation: public FieldDynamics
{
public:
    FD_Rotation(float radius, ofVec2f pos, float speed);
    void update(
        float dt,
        ofFloatPixels& VF,
        ofFbo& Field) override;
    
private:
    float _speed;
    
    ofFloatImage _img;
    
};

#endif /* FD_Rotation_hpp */
