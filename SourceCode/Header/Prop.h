#include "CommonClass.h"

// 道具类，管理道具的数据
class prop
{
private:
    CSprite *m_pProp;
    int m_iPropNum;

    CSprite *m_pPropInTable;

public:
    prop();
    ~prop();

    // PropInit: 初始化道具
    void PropInit(int tmp_PropNum);

    // IntoPropTable: 道具进入道具栏
    void IntoPropTable();

    //
};