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

    // GetPropNumByName: 根据道具名返回编号
    int GetPropNumByName(const char * PropName);

    //PropUpdate: 根据道具编号更新道具
    void PropUpdate(int tmp_PropNum);

};