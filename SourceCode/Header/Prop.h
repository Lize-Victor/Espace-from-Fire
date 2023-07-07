#include "CommonClass.h"


// 道具类，管理道具的数据
class prop
{
private:
    CSprite *m_pProp;


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