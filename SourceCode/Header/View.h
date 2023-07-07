#include "CommonClass.h"
class view
{
private:
    CSprite *m_pViewUp;
    CSprite *m_pViewDown;

public:
    view();

    void ViewInit();
    // 当中层为2楼时，将下层上移一层
    void MoveViewDown();
    // 当中层为8楼上，人物上9楼，则向下移一层
    void MoveViewUp();
};