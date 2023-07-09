/*
 */

#ifndef _CUSTOM_FUNCTION_H_
#define _CUSTOM_FUNCTION_H_

#include "Floor.h"
#include <vector>
using std::vector;
// FloorMove: 竖直移动楼层
//  参数 tmp_iFloorNum: 范围 -1~7
//  参数 l_floor： 楼层向量
void FloorMove(int tmp_iFloorNum, vector<Floor *> &l_floor);

#endif