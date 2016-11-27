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
	// 继承自FieldDynamics
{
public:
	// 构造函数
    FD_Rotation(float radius, ofVec2f pos, float speed);
    // 更新：随时间变化，旋转区域内矢量场的内容
	void update(
        float dt,
        ofFloatPixels& VF,
        ofFbo& Field) override; // 对虚函数的重写
    
private:
    float _speed; // 速度
    
    ofFloatImage _img; 
    
};

#endif /* FD_Rotation_hpp */
