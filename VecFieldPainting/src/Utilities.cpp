//
//  Utilities.cpp
//  VecFieldPainting
//
//  Created by Bentley on 16/11/19.
//
//

#include <stdio.h>
#include "Utilities.h"

ofVec2f utils::floatColor2Vec2f(
            ofFloatColor cr, float offset, float scale)
{
    ofVec2f v(cr.r-offset,cr.g-offset);
    v *= scale;
    return v;
}

void utils::drawVecField(ofFloatPixels& VField, ofRectangle R, int res, float arrowSize, bool bUseAlpha)
{
    int w,h;
    w = VField.getWidth();
    h = VField.getHeight();
    
    int rw,rh;
    rw = R.width;
    rh = R.height;
    
    float sx,sy;
    sx = (float)rw/(float)w;
    sy = (float)rh/(float)h;
    
    ofStyle S = ofGetStyle();
    ofFloatColor CrS = S.color;
    
    ofPushMatrix();
    ofTranslate(R.x, R.y,0.0f);
    ofScale(sx,sy,1.0f);
    
    for(int row=0;row<w;row += res)
    {
        for(int col=0;col<h;col+=res)
        {
            ofFloatColor cr =
            VField.getColor(row, col);
            ofFloatColor c(CrS);
            if(bUseAlpha)
            {
                c.a *= cr.a;
            }
            ofSetColor(c);
            ofVec2f v =
            utils::floatColor2Vec2f(cr,0.5f,res*0.4f);
            ofVec2f pos(row,col);
            ofVec2f S = pos-v;
            ofVec2f E = pos+v;
            ofDrawArrow(S, E, arrowSize);
        }
    }
    ofPopMatrix();
}


