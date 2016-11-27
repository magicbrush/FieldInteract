//
//  FieldDynamics.cpp
//  VecFieldPainting
//
//  Created by Bentley on 16/11/19.
//
//

#include "FieldDynamics.hpp" // 本类的头文件

// 构造函数：初始化位置和大小
FieldDynamics::FieldDynamics(ofVec2f pos, float radius):
_radius(radius),
_pos(pos)
{}

float FieldDynamics::getAffectStrength(ofVec2f _target)
//离中心位置越远，处理强度越小，且虽距离增加，线性降低
{
    ofVec2f offset = _target-_pos;
    float dist = offset.length();
    float affect = ofMap(dist,0,_radius,1.0f,0.0f,true);
    return affect;
}

//默认显示效果：画一个半透明黑色圆形，显示作用范围
void FieldDynamics::draw()
{
    ofPushStyle();
    ofSetColor(0,0,0,20);
    ofDrawCircle(_pos, _radius);
    ofPopStyle();
}
