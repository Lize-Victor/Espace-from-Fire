#include "CommonClass.h"

// 道具类，管理道具的数据
class prop
{
private:
    CSprite *m_pProp;
    int m_iPropNum; // 压力钳：1   枕头：2   窗帘：3   毛巾：4   灭火器：5

    CSprite *m_pPropInTable;
public:
    prop();
    ~prop();

    // PropInit: 初始化道具
    void PropInit(int tmp_PropNum);

    // IntoPropTable: 道具进入道具栏
    void IntoPropTable();

    // OutPropTable: 丢弃道具
    // 参数 tmp_PersonPoiX：丢弃道具时，人物所在位置X
    // 参数 tmp_PersonPoiY：丢弃道具时，人物所在位置Y
    void OutPropTable(float tmp_PersonPoiX, float tmp_PersonPoiY);

    // GetPropNumByName: 根据道具名返回编号
    int GetPropNumByName(const char * PropName);

    //PropUpdate: 根据道具编号更新道具
    void PropUpdate(int tmp_PropNum);

};