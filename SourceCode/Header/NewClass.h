#ifndef _NEW_CLASS_H_
#define _NEW_CLASS_H_

#include <CommonClass.h>

#include "MacroDefinition.h"


struct Point
{
    float X;
    float Y;
};

// 角色类，管理角色的数据
class person
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
// warning::: must using continuous address
class Floor
{
private:
    CSprite *m_pFloor; // 楼层元

    Point m_PFloorPoi; // 楼层坐标
    int m_iFloorNum;   // 楼层编号 , 范围 1~12

    CAnimateSprite *m_pFire[ONE_FLOOR_CELL_X_NUMBER]; // 火焰
    bool m_bFireState[ONE_FLOOR_CELL_X_NUMBER];
    float CurTime_Fire_X;
    float CurTime_Fire_Y;
    CAnimateSprite *m_pFireY[2][3]; // 单层火焰状态记录
    bool m_bFireStateY[2][3];       // 记录火焰的纵向状态数据

    CAnimateSprite *m_pSmog[ONE_FLOOR_CELL_Y_NUMBER - 1][ONE_FLOOR_CELL_X_NUMBER]; // 烟雾元
    float CurTime_Smog_X;
    bool m_bSmogState[ONE_FLOOR_CELL_Y_NUMBER - 1][ONE_FLOOR_CELL_X_NUMBER]; // 单层烟雾状态记录

    float CurTime_Smog_Produce;

    CAnimateSprite *m_pSmogWarning;

    CSprite *m_pDoor;
    bool m_bDoorState;
public:
    Floor();
    ~Floor();

    // GET
    CSprite *GetFloor()
    {
        return m_pFloor;
    }
    int GetFloorNum()
    {
        return m_iFloorNum;
    }
    float GetFloorPoiX()
    {
        return m_PFloorPoi.X;
    }
    float GetFloorPoiY()
    {
        return m_PFloorPoi.Y;
    }

    // SET
    void SetFloorPosition(float X, float Y)
    {
        m_PFloorPoi.X = X;
        m_PFloorPoi.Y = Y;
    }
    // FloorInit: 初始化楼层
    // 参数 FloorInit: 楼层号码
    void FloorInit(int iFloorNum);
    // FireInit: 初始化火焰
    void FireInit();
    // SmogInit: 初始化烟雾
    void SmogInit();

    // FloorUpdate: 更新楼层状态到引擎
    void FloorUpdate();

    // FireDiffusionX: 火焰横向扩散
    // 参数 fTimeDelta: 两次调用的时间间隔
    void FireDiffusionX(float fTimeDelta);

    // FireDiffusionY: 火焰纵向扩散
    // 参数 fTimeDelta: 两次调用的时间间隔
    // 参数 thisFloor: 着火源楼层
    void FireDiffusionY(float fTimeDelta);

    // FireBoom: 火焰爆发
    void FireBoom();

    // SmogDiffusionX: 烟雾横向扩散
    // 参数 fTimeDelta: 两次调用的时间间隔
    void SmogDiffusionX(float fTimeDelta);

    // FireProduceSmog: 由火焰生成烟雾
    // 参数 fTimeDelta: 两次调用的时间间隔
    void FireProduceSmog(float fTimeDelta);


    // SmogWarningInit: 烟雾报警器初始化
    void SmogWarningInit();

    // SmogWarningBing: 报警器响
    void SmogWarningBing();
};
#endif