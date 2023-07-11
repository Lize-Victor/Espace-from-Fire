/*
 */

#ifndef _CUSTOM_FUNCTION_H_
#define _CUSTOM_FUNCTION_H_

#include "Floor.h"
#include <vector>
using std::vector;
// FloorMove: 进行楼层的平移
// 参数 cur_FloorNum:当前的楼层 范围1~9
// 参数 tmp_FloorNum:目标楼层 范围-1~7
// 参数 l_floor: 楼层向量
void FloorMove(int cur_FloorNum, int tmp_iFloorNum, vector<Floor *> &l_floor);

// FireHurt: 火焰伤害
// 参数 tmp_Blood: 血量
void FireHurt(int &tmp_Blood);

// Somg: 烟雾伤害
// 参数 tmp_Blood: 血量
// 参数 tmp_PropNum: 人物携带的道具编号
void SmogHurt(int &tmp_Blood, int tmp_PropNum);
#endif