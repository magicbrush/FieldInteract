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
	// 定义了一个基类，用来时限对矢量场局部区域的动态化处理
{
public:
	// 构造函数：初始化这个对象的位置pos和影响范围大小radius
    FieldDynamics(ofVec2f pos, float radius);
	// 更新：即对矢量场进行动态化处理，定义为存虚函数，让子类来实现这一概念
    virtual void update(float dt, ofFloatPixels& VF, ofFbo& Field) = 0;
	// 显示：用于再屏幕上显示自己，定义为虚函数，设定一种默认的显示效果，即显示作用范围
	// 但也允许子类自己定义特殊的显示效果
    virtual void draw();
    
protected:
	// 定义一个供所有子类均可调用的函数，用于计算某个处理位置的强度
    float getAffectStrength(ofVec2f _target);
    
	// 基本属性有两种，位置和半径
	// 这两种属性是所有子类共同需要的属性
    ofVec2f _pos;
    float _radius;
    
};

#endif /* FieldDynamics_hpp */
