/*

*/

#ifndef _NEW_CLASS_H_
#define _NEW_CLASS_H_

#include <CommonClass.h>

#define ONE_FLOOR_CELL_NUMBER 10

#define FIRE_HURT_COEFFICIENT
#define SMOG_HURT_COEFFICIENT

#define PERSON_NORMAL_SPEED
#define PERSON_FULL_BLOOD 100

struct Point
{
    float X;
    float Y;
};

// 角色类，管理角色的数据
class person : public CAnimateSprite
{
private:
    CAnimateSprite *m_pPerson;

    Point m_PPersonPoi;   // 角色坐标
    Point m_PPersonSpeed; // 角色速度
    int m_iPersonBlood;   // 角色血量

    bool m_bPersonDirection; // 角色方向 1：朝左 2：朝右
    bool m_bProp;            // 是否携带道具 1：携带 2：不携带

public:
    person();
    ~person();

    // PersonInit: 初始化角色
    void PersonInit();

    // PersonUpdate: 更新角色状态到引擎
    void PersonUpdate();
};

// 楼层类，管理单层楼的数据
class floor : public CSprite
{
private:
    CSprite *m_pFloor; // 楼层元

    Point m_PFloorPoi; // 楼层坐标
    int m_iFloorNum;   // 楼层编号

    CAnimateSprite *m_pFire; // 火焰元
    bool m_bFireState[ONE_FLOOR_CELL_NUMBER]; // 单层火焰状态记录

    CAnimateSprite *m_pSmog; // 烟雾元
    bool m_bSmogState[ONE_FLOOR_CELL_NUMBER];  // 单层烟雾状态记录

    prop *m_pPliers; // 钳子元



public:
    floor();
    ~floor();

    // FloorInit: 初始化楼层
    void FloorInit();

    // FloorUpdate: 更新楼层状态到引擎
    void FloorUpdate();

    // FireDiffusion: 火焰扩散
    void FireDiffusion();

    // SmogDiffusion: 烟雾扩散
    void SmogDiffusion();


};

// 道具类，管理道具的数据
class prop : public CSprite
{
private:
    CSprite *m_pProp;

    Point m_PPropPoi;

public:
    prop();
    ~prop();

    // PropInit: 初始化道具
    void PropInit();

    // PropUpdate: 更新道具的状态到引擎
    void PropUpdate();

    // IntoPropTable: 道具进入道具栏
    void IntoPropTable();

    //
};
#endif