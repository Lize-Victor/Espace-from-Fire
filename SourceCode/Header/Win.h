#include "CommonClass.h"

class Win
{
private:
    CSprite *m_pWin;
    bool m_bWinLockState; // 0：未锁    1：锁
public:
    Win();
    ~Win();


    // Get
    // GetWinLockState： 获取窗户状态
    // 返回值： 0: 未锁        1：锁
    bool GetWinLockState()
    {
        return m_bWinLockState;
    }

    void WindowInit(bool tmp_WinLockState);

    void WindowUpdate(bool tmp_WinLockState);
};