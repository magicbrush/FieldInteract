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
	// 矢量场尺寸
    int w = VF.getWidth();
    int h = VF.getHeight();
    
	// _img用于保存处理结果的中间量
	// 若_img没有初始化，则初始化
    int radius = (int)_radius;
    if(_img.getWidth()!=radius*2 || _img.getHeight()!=radius*2)
    {
        _img.allocate(2*radius,2*radius,OF_IMAGE_COLOR_ALPHA);
    }
    
	// 计算对矢量场的改变，计算结果保存到中间存储对象_img中
    int col(0),row(0);
    for(int i=_pos.x-_radius;i<_pos.x+_radius;i++)
    {
        row=0;
        for(int j=_pos.y-_radius;j<_pos.y+_radius;j++)
        {
            ofVec2f p(i,j);
			// 获得当前处理像素位置p的作用强度af
            float af = getAffectStrength(p);
            
			// 只有作用强度af大于0时，才进行处理
            if(af>0)
            {
				// 若处理位置超出屏幕范围，则
				// 将其转化为屏幕另一头的对应位置
                int i2,j2;
                i2 = ofWrap(i,0,w);
                j2 = ofWrap(j,0,h);
                
				// 将VF中当前位置的颜色转化为一个矢量v
                ofFloatColor cr = VF.getColor(i2,j2);
                ofVec2f v = utils::floatColor2Vec2f(cr,0.5,1.0f);
                
				// 旋转一定角度
                v.rotate(dt*_speed);
                v.limit(300); // 限制长度
				// 获得结果，然后保存到暂存空间_img中
                ofFloatColor cr2(v.x+0.5f,v.y+0.5f,0.0f,1.0f);
                _img.setColor(col,row,cr2);
            }
			else
				// 若af不大于0，则再暂存空间中保存0矢量（对应色彩为灰色）
			{
				_img.setColor(col, row, ofFloatColor(0.5f, 0.5f, 0.5f, 1.0f));
			}            
            row++;
        }
        col++;
    }  
	// 暂存图更新
    _img.update();
    
	// 用暂存图向目标绘制
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
