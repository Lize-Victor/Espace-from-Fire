#include "Win.h"
#include "MacroDefinition.h"

Win::Win()
{
    m_bWinLockState = 0;
    m_pWin = nullptr;
}

void Win::WindowInit(bool tmp_WinLockState)
{
    m_pWin = new CSprite(WIN_API_NAME);
    m_pWin->SetSpriteCollisionReceive(true);

    m_bWinLockState = tmp_WinLockState;
}

void Win::WindowUpdate(bool tmp_WinLockState)
{
    m_bWinLockState = tmp_WinLockState;
}
