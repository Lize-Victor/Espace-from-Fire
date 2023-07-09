#include "CommonClass.h"

class Win
{
private:
    CSprite *m_pWin;
    bool m_bWinLockState; // 0：未锁    1：锁
public:
    Win();
    ~Win();

    void WindowInit(bool tmp_WinLockState);

    void WindowUpdate();
};