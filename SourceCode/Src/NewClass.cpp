/*

*/

#include "NewClass.h"
#include <random>
#include <cmath>
#include <time.h>
#include <vector>

using std::vector;

floor::floor()
{
    m_pFloor = nullptr;
    m_PFloorPoi.X = 0;
    m_PFloorPoi.Y = 0;
    m_iFloorNum = 0;

    for (int i = 0; i < ONE_FLOOR_CELL_NUMBER; i++)
    {
        m_pFire[i] = nullptr;
        m_bFireState[i] = 0;
    }

    for (int i = 0; i < ONE_FLOOR_CELL_NUMBER; i++)
    {
        m_pSmog[i] = nullptr;
        m_bFireState[i] = 0;
    }

    m_pDoor = nullptr;
    m_bDoorState = 0;
}

void floor::FloorInit(int iFloorNum)
{
    char *destName = CSystem::MakeSpriteName("Floor", iFloorNum);
    m_pFloor = new CSprite(destName);
    m_pFloor->CloneSprite(FLOOR_API_NAME);
    m_PFloorPoi.X = FLOOR_START_X;
    m_PFloorPoi.Y = FLOOR_START_Y - iFloorNum * FLOOR_Y;
    m_iFloorNum = iFloorNum;

    FloorUpdate();
}

void floor::FireInit()
{
    for (int i = 0; i < ONE_FLOOR_CELL_NUMBER; i++)
    {
        char *destName = CSystem::MakeSpriteName("Fire", i);
        m_pFire[i] = new CAnimateSprite(destName);
        m_pFire[i]->CloneSprite(FIRE_API_NAME);
    }
}

void floor::SmogInit()
{
    for (int i = 0; i < ONE_FLOOR_CELL_NUMBER; i++)
    {
        char *destName = CSystem::MakeSpriteName("Smog", i);
        m_pSmog[i] = new CAnimateSprite(destName);
        m_pSmog[i]->CloneSprite(SMOG_API_NAME);
    }
}
void floor::FloorUpdate()
{
    m_pFloor->SetSpritePosition(m_PFloorPoi.X, m_PFloorPoi.Y);

    // 更新火焰
    for (int i = 0; i < ONE_FLOOR_CELL_NUMBER; i++)
    {
        if (m_bFireState[i] == 1)
        {
            m_pFire[i]->SetSpritePosition(m_PFloorPoi.X + i * FLOOR_CELL_X, m_PFloorPoi.Y);
        }
    }

    // 更新烟雾
    for (int i = 0; i < ONE_FLOOR_CELL_NUMBER; i++)
    {
        if (m_bSmogState[1] == 1)
        {
            m_pSmog[i]->SetSpritePosition(m_PFloorPoi.X + i * FLOOR_CELL_X, m_PFloorPoi.Y + FIRE_Y);
        }
    }
}

void floor::FireDiffusion(float fTimeDelta)
{
    static float CurTime = FIRE_DIFFUSION_TIME;
    CurTime -= fTimeDelta;

    if (CurTime < 1e-6)
    {
        bool tmp_FireState[ONE_FLOOR_CELL_NUMBER] = {}; // 记录这次火焰传播后的数据
        CurTime = FIRE_DIFFUSION_TIME;
        // 判断中间单元格的扩散，防越界
        for (int i = 1; i < ONE_FLOOR_CELL_NUMBER - 1; i++)
        {
            if (m_bFireState[i] = true)
            {
                tmp_FireState[i - 1] = 1;
                tmp_FireState[i + 1] = 1;
                tmp_FireState[i] = 1;
            }
        }

        // 判断两端向中传播
        if (m_bFireState[0] == true)
        {
            tmp_FireState[1] = 1;
        }
        if (m_bFireState[ONE_FLOOR_CELL_NUMBER - 1] == true)
        {
            tmp_FireState[ONE_FLOOR_CELL_NUMBER - 2] = 1;
        }

        // 对现状态进行更新
        for (int i = 0; i < ONE_FLOOR_CELL_NUMBER; i++)
        {
            m_bFireState[i] = tmp_FireState[i];
        }
        FloorUpdate();
    }
}

void floor::SmogDiffusion(float fTimeDelta)
{
    static float CurTime = SMOG_DIFFUSION_TIME;
    CurTime -= fTimeDelta;

    if (CurTime < 1e-6)
    {
        bool tmp_SmogState[ONE_FLOOR_CELL_NUMBER] = {};
        CurTime = SMOG_DIFFUSION_TIME;

        for (int i = 1; i < ONE_FLOOR_CELL_NUMBER - 1; i++)
        {
            if (m_bSmogState[i] = true)
            {
                tmp_SmogState[i - 1] = 1;
                tmp_SmogState[i + 1] = 1;
                tmp_SmogState[i] = 1;
            }
        }
        if (m_bSmogState[0] == true)
        {
            tmp_SmogState[1] = 1;
        }
        if (m_bSmogState[ONE_FLOOR_CELL_NUMBER - 1] == true)
        {
            m_bSmogState[ONE_FLOOR_CELL_NUMBER - 2] = 1;
        }

        for (int i = 0; i < ONE_FLOOR_CELL_NUMBER; i++)
        {
            m_bSmogState[i] = tmp_SmogState[i];
        }

        FloorUpdate();
    }
}
