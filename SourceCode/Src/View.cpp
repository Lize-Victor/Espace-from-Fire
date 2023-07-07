#include "View.h"

view::view()
{
    m_pViewDown = nullptr;
    m_pViewUp = nullptr;
}

void view::ViewInit()
{
    m_pViewUp = new CSprite("viewup");
    m_pViewDown = new CSprite("viewdown");

    m_pViewDown->SetSpriteCollisionResponse(COL_RESPONSE_OFF);
    m_pViewUp->SetSpritePosition(75,-68);
    m_pViewDown->SetSpritePosition(75,-20);
}

void view::MoveViewDown()
{
    m_pViewDown->SetSpritePosition(75,-44);
}

void view::MoveViewUp()
{
    m_pViewUp->SetSpritePosition(75,-44);
}
