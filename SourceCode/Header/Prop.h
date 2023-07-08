#include "CommonClass.h"


// 道具类，管理道具的数据
class prop
{
private:
    CSprite *m_pProp;
    char * m_pPropName;

    CSprite *m_pPropInTable;

public:
    prop(const char *destName);
    ~prop();

    // PropInit: 初始化道具
    void PropInit(int i_floor);

    // IntoPropTable: 道具进入道具栏
    void IntoPropTable();

    //
};