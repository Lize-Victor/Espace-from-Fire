#ifndef _FLOOR_H_
#define _FLOOR_H_

#include <CommonClass.h>

#include "MacroDefinition.h"

struct Point
{
    float X;
    float Y;
};

// 楼层类，管理单层楼的数据
// warning::: must using continuous address
class Floor
{
private:
    CSprite *m_pFloor; // 楼层元

    Point m_PFloorPoi; // 楼层坐标

    CTextSprite *m_pFloorNum;
    int m_iFloorNum; // 楼层编号 , 范围 1~12

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

    CAnimateSprite *m_pSmogWarning; // 烟雾报警器

    CSprite *m_pDoor;         // 逃生通道门
    static bool m_bDoorState; // 逃生通达门的状态

    int m_iPropNum; // 压力钳：1   枕头：2   窗帘：3   毛巾：4   灭火器：5

    bool m_bWinstate;
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
    int GetPropNum()
    {
        return m_iPropNum;
    }
    bool GetWinLockState()
    {
        return m_bWinstate;
    }

    // SET
    void SetFloorPosition(float X, float Y)
    {
        m_PFloorPoi.X = X;
        m_PFloorPoi.Y = Y;
    }

    void SetFloorNumVisble(bool tmp_State)
    {
        m_pFloorNum->SetSpriteVisible(tmp_State);
    }

    void SetPropNum(int tmp_PropNum)
    {
        m_iPropNum = tmp_PropNum;
    }

    void SetWinState(bool tmp_WinState)
    {
        m_bDoorState = tmp_WinState;
    }

    // 参数tmp_State：门的开关，默认使用类中保存的状态
    void SetDoorVisble(bool tmp_State = m_bDoorState);

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

    // ExtinguisherOutFire： 灭火器灭火  灭整层的火
    void ExtinguisherOutFire();
};
#endif