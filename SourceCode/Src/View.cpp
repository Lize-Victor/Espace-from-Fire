#include "View.h"

view::view()
{
    m_pViewDown = nullptr;
    m_pViewUp = nullptr;
}

void view::ViewInit(int tmp_iGameLevel)
{
    m_pViewUp = new CSprite("viewup");
    m_pViewDown = new CSprite("viewdown");
    m_pViewTop = new CSprite("viewtop");
    m_pViewBottom = new CSprite("viewbottom");

    if (tmp_iGameLevel == 3)
    {
        m_pViewUp->SetSpritePosition(75, -68);
        m_pViewDown->SetSpritePosition(75, -20);
        m_pViewTop->SetSpritePosition(75, -68);
        m_pViewBottom->SetSpritePosition(75, -20);
    }

    m_pViewTop->SetSpriteVisible(false);
    m_pViewBottom->SetSpriteVisible(false);
}

void view::SetViewVisble(bool tmp_bVisbleState)
{
    m_pViewDown->SetSpriteVisible(tmp_bVisbleState);
    m_pViewUp->SetSpriteVisible(tmp_bVisbleState);
}

void view::ShowViewTop(bool tmp_bVisbleState)
{
    m_pViewTop->SetSpriteVisible(tmp_bVisbleState);
}

void view::ShowViewBottom(bool tmp_bVisbleState)
{
    m_pViewBottom->SetSpriteVisible(tmp_bVisbleState);
}
