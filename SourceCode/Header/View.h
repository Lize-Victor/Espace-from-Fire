#include "CommonClass.h"
class view
{
private:
    CSprite *m_pViewUp;
    CSprite *m_pViewDown;

    CSprite *m_pViewTop;
    CSprite *m_pViewBottom;
public:
    view();

    void ViewInit();

    void SetViewVisble(bool tmp_bVisbleState);

    // 显示 顶层
    void ShowViewTop(bool tmp_bVisbleState);
    // 显示 底层
    void ShowViewBottom(bool tmp_bVisbleState);
};