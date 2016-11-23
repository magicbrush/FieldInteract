//
//  FD_Rotation.cpp
//  VecFieldPainting
//
//  Created by Bentley on 16/11/19.
//
//

#include "FD_Rotation.hpp"
#include "utilities.h"


FD_Rotation::FD_Rotation(
                         float radius, ofVec2f pos, float speed):
FieldDynamics(pos,radius),
_speed(speed)
{
}

void FD_Rotation::update(
    float dt,
    ofFloatPixels& VF,
    ofFbo& Field)
{
    int w = VF.getWidth();
    int h = VF.getHeight();
    
    int radius = (int)_radius;
    if(_img.getWidth()!=radius*2 || _img.getHeight()!=radius*2)
    {
        _img.allocate(2*radius,2*radius,OF_IMAGE_COLOR_ALPHA);
    }
    
    int col(0),row(0);
    for(int i=_pos.x-_radius;i<_pos.x+_radius;i++)
    {
        row=0;
        for(int j=_pos.y-_radius;j<_pos.y+_radius;j++)
        {
            ofVec2f p(i,j);
            float af = getAffectStrength(p);
            
            if(af>0)
            {
                int i2,j2;
                i2 = ofWrap(i,0,w);
                j2 = ofWrap(j,0,h);
                
                ofFloatColor cr = VF.getColor(i2,j2);
                ofVec2f v = utils::floatColor2Vec2f(cr,0.5,1.0f);
                
                v.rotate(dt*_speed);
                v.limit(300);
                ofFloatColor cr2(v.x+0.5f,v.y+0.5f,0.0f,1.0f);
                _img.setColor(col,row,cr2);
            }
			else
			{
				_img.setColor(col, row, ofFloatColor(0.5f, 0.5f, 0.5f, 1.0f));
			}
            
            row++;
        }
        col++;
    }
    
    _img.update();
    
    Field.begin();
    ofPushMatrix();
    ofPushStyle();
    int startX,startY;
    startX = _pos.x - _radius;
    startY = _pos.y - _radius;
    int diameter = 2*_radius;
    _img.draw(startX,startY,diameter,diameter);
    
    ofPopStyle();
    ofPopMatrix();
    Field.end();
}
