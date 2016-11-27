//
//  Utilities.h
//  VecFieldPainting
//
//  Created by Bentley on 16/11/19.
//
//

#ifndef Utilities_h
#define Utilities_h
#include "ofMain.h"

namespace utils {
	//　将色彩转化为矢量
    ofVec2f floatColor2Vec2f(
                             ofFloatColor cr, float offset = 0.5f, float scale=10.0f);
    
	//　绘制矢量场
    void drawVecField(ofFloatPixels& VField, ofRectangle R, int res = 15, float arrowSize = 2.0f, bool bUseAlpha = false);
};


#endif /* Utilities_h */
