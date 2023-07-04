/*
*/

#ifndef _CUSTOM_FUNCTION_H_
#define _CUSTOM_FUNCTION_H_

#include "NewClass.h"
#include <vector>
using std::vector;
//FloorMove: 竖直移动楼层
// 参数 deltaY： 移动量 向上为负，向下为正
// 参数 l_floor： 楼层向量
void FloorMove(float deltaY, vector<Floor *> &l_floor);


#endif