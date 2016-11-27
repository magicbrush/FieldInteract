//
//  DrawingParticle.cpp
//  VecFieldPainting
//
//  Created by Bentley on 16/11/19.
//
//

#include "DrawingParticle.hpp" // 本类的头文件
#include "Utilities.h" // 工具函数都放在这个头文件的

void DrawingParticle::updatePosition(
    float dt,
    ofFloatPixels& VecField)
{
	// 从矢量场VecField获得当前位置pos的颜色
    ofFloatColor vecCr =
        VecField.getColor(_pos.x, _pos.y);
	// 将颜色转化为一个矢量，作为速度vec使用
    ofVec2f vec =
        utils::floatColor2Vec2f(vecCr, 0.5f, _speed);
    
	// 按速度vec移动量move
    ofVec2f move =dt * vec / (0.01f*_radius*_radius);

	// 获得自己颜色的色相Hue
    float hue = 360.0f*(float)_color.getHue()/255.0f;

	// 移动量旋转一定角度，即色相hue
    move.rotate(hue);
    
	// 移动到新位置
    _pos += move;
    
	// 若超出屏幕范围，则跳转到屏幕另一边
    ofRectangle R(0,0,ofGetWidth(),ofGetHeight());
    if(!R.inside(_pos))
    {
        _pos.x = ofWrap(_pos.x,0,ofGetWidth());
        _pos.y = ofWrap(_pos.y,0,ofGetHeight());
    }
    
	// 按跃迁概率随即跃迁
    float rvalue = ofRandom(1.0f);
    if(rvalue<_wrapProb*dt)
    {
        _pos.x = ofRandom(0,VecField.getWidth());
        _pos.y = ofRandom(0,VecField.getHeight());
    }
}

void DrawingParticle::draw()
{
	// 画个圆形
    ofPushStyle();
    ofSetColor(_color);
    ofDrawCircle(_pos, _radius);
    ofPopStyle();
}

void DrawingParticle::drawVisualAids()
{
    // 画额外的东西：黑色边线
    ofPushStyle();
    ofNoFill();
    ofSetColor(0,0,0,255);
    ofDrawCircle(_pos, _radius);
    ofPopStyle();
}
// 构造函数：初始化属性
DrawingParticle::DrawingParticle(
                float radius,
                ofColor cr,
                ofVec2f pos,
                float spd,
                float wrapProb):
_radius(radius),
_color(cr),
_pos(pos),
_speed(spd),
_wrapProb(wrapProb)
{}
