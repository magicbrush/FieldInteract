//
//  DrawingParticle.hpp
//  VecFieldPainting
//
//  Created by Bentley on 16/11/19.
//
//

// #ifndef ... #def ...   #endif
// 用于放置本头文件被重复包含
#ifndef DrawingParticle_hpp
#define DrawingParticle_hpp

#include <stdio.h>
#include "ofMain.h" // 用到OF的功能，必须包含此头文件

class DrawingParticle
// 本类的能力：根据自身颜色，随着所在的矢量场移动，并且再移动过程中，向画布绘制
{
public:
	// 构造函数
    DrawingParticle(
        float radius=10.0f,
        ofColor cr= ofColor::green,
        ofVec2f pos = ofVec2f(0,0),
                    float spd=100.0f,
        float wrapProb = 0.03f);
    
	// 根据经过的时间dt，从矢量场VecField获得所在位置的矢量，将其
	// 作为当前的速度，移动到新位置
    void updatePosition(float dt, ofFloatPixels& VecField);

	// 按自己的位置/颜色/尺寸画一个圆形
    void draw();

	// 画辅助信息
    void drawVisualAids();
    
private:
    float _radius; // 半径
    ofColor _color;// 颜色
    ofVec2f _pos;// 位置
    float _speed; // 速度
    float _wrapProb; // 跃迁（瞬间移动）发生概率
    
};

#endif /* DrawingParticle_hpp */
