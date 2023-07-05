#ifndef _NEW_CLASS_H_
#define _NEW_CLASS_H_

#include <CommonClass.h>

#define FLOOR_API_NAME "floor"
#define FLOOR_HEIGHT_NUM 9
#define ONE_FLOOR_CELL_X_NUMBER 15 // 范围 1~10
#define ONE_FLOOR_CELL_Y_NUMBER 3 // 范围 1~
#define FLOOR_X 150
#define FLOOR_Y 24
#define FLOOR_CELL_X 9.9
#define FLOOR_CELL_Y 8.109
#define FLOOR_START_X 75.000
#define FLOOR_START_Y -12.000
#define ELEVATOR_CELL_NUMBER 7 // 范围 7 8
#define STAIRS_CELL_NUMBER 15 // 范围 1~10

#define FIRE_API_NAME "fire"
#define FIRE_X 9.711
#define FIRE_Y 8.109
#define FIRE_START_X 6.396
#define FIRE_START_Y -4.054
#define FIRE_HURT_COEFFICIENT
#define FIRE_DIFFUSION_X_TIME 3.f
#define FIRE_DIFFUSION_Y_TIME 2.f

#define SMOG_API_NAME "Smog"
#define SMOG_X 9.711
#define SMOG_Y 7.076
#define SMOG_START_X 6.363
#define SMOG_START_Y -12.538

#define SMOG_HURT_COEFFICIENT
#define SMOG_DIFFUSION_X_TIME 2.F
#define SMOG_DIFFUSION_Y_TIME 1.F

#define FIRE_PRODUCE_SMOG_TIME 1.f

#define DOOR_API_NAME ""

#define PERSON_NORMAL_SPEED
#define PERSON_FULL_BLOOD 100

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

    CAnimateSprite *m_pFire[ONE_FLOOR_CELL_X_NUMBER]; // 火焰元
    bool m_bFireState[ONE_FLOOR_CELL_X_NUMBER];       // 单层火焰状态记录

    CAnimateSprite *m_pSmog[ONE_FLOOR_CELL_Y_NUMBER-1][ONE_FLOOR_CELL_X_NUMBER]; // 烟雾元
    bool m_bSmogState[ONE_FLOOR_CELL_Y_NUMBER-1][ONE_FLOOR_CELL_X_NUMBER];       // 单层烟雾状态记录

    CAnimateSprite *m_pDoor;
    bool m_bDoorState;

public:
    Floor();
    ~Floor();

    // GET
    CSprite *GetFloor()
    {
        return m_pFloor;
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
    // DoorInit: 初始化门
    void DoorInit();

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
};

// 道具类，管理道具的数据
class prop
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