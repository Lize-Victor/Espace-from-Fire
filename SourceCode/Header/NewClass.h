/*

*/

#ifndef _NEW_CLASS_H_
#define _NEW_CLASS_H_

#include <CommonClass.h>

struct Point
{
    float X;
    float Y;
};

//角色类，管理角色的数据
class person : public CAnimateSprite
{
private:
    CAnimateSprite *m_pPerson;

    Point m_PPersonPoi;      // 角色坐标
    Point m_PPersonSpeed;    // 角色速度
    bool m_bPersonDirection; // 角色方向 1：朝左 2：朝右

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
    CSprite *m_pFloor;

    Point m_PFloorPoi; // 楼层坐标
    int m_iFloorNum;   // 楼层编号

public:
    floor();
    ~floor();

    // FloorInit: 初始化楼层
    void FloorInit();

    // FloorUpdate: 更新楼层状态到引擎
    void FloorUpdate();
};

//道具类，管理道具的数据
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

    // PropUpdate:
    void PropUpdate();
};
#endif