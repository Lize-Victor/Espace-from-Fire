﻿#include "NewClass.h"
#include <random>
#include <cmath>
#include <ctime>
#include <vector>

using std::vector;

Floor::Floor()
{
    m_pFloor = nullptr;
    m_PFloorPoi.X = 0;
    m_PFloorPoi.Y = 0;
    m_iFloorNum = 0;

    for (int i = 0; i < ONE_FLOOR_CELL_X_NUMBER; i++)
    {
        m_pFire[i] = nullptr;
        m_bFireState[i] = 0;
    }

    for (int j = 0; j < ONE_FLOOR_CELL_Y_NUMBER - 1; j++)
    {
        for (int i = 0; i < ONE_FLOOR_CELL_X_NUMBER; i++)
        {
            m_pSmog[j][i] = nullptr;
            m_bSmogState[j][i] = 0;
        }
    }

    m_pDoor = nullptr;
    m_bDoorState = 0;
}
void Floor::FloorInit(int iFloorNum)
{
    char *destName = CSystem::MakeSpriteName("Floor", iFloorNum);
    m_pFloor = new CSprite(destName);
    m_pFloor->CloneSprite(FLOOR_API_NAME);
    m_PFloorPoi.X = FLOOR_START_X;
    m_PFloorPoi.Y = FLOOR_START_Y - (iFloorNum - 1) * FLOOR_Y;
    m_iFloorNum = iFloorNum;

    FloorUpdate();
}

void Floor::FireInit()
{
    for (int i = 0; i < ONE_FLOOR_CELL_X_NUMBER; i++)
    {
        char *destName = CSystem::MakeSpriteName("Fire", i);
        m_pFire[i] = new CAnimateSprite(destName);
        m_pFire[i]->CloneSprite(FIRE_API_NAME);
    }
    for (int j = 0; j < ; j++)
    {

    }

}

void Floor::SmogInit()
{
    for (int j = 0; j < ONE_FLOOR_CELL_Y_NUMBER - 1; j++)
    {
        for (int i = 0; i < ONE_FLOOR_CELL_X_NUMBER; i++)
        {
            char *destName1 = CSystem::MakeSpriteName("Smog", j + 1);
            char *destName = CSystem::MakeSpriteName(destName1, i);
            m_pSmog[j][i] = new CAnimateSprite(destName);
            m_pSmog[j][i]->CloneSprite(SMOG_API_NAME);
        }
    }
}

void Floor::DoorInit()
{
    char *destName = CSystem::MakeSpriteName("Door", m_iFloorNum);
    m_pDoor = new CAnimateSprite(destName);
    m_pDoor->CloneSprite(DOOR_API_NAME);
    srand(time(nullptr));
    int m_bDoorState = rand() % 2;
}
void Floor::FireDiffusionY(float fTimeDelta)
{
    float CurTime = FIRE_DIFFUSION_Y_TIME;
    CurTime -= fTimeDelta;
    if (CurTime < 1e-6)
    {
        CurTime = FIRE_DIFFUSION_Y_TIME;

        if (m_bFireState[ELEVATOR_CELL_NUMBER - 1])
        {
        }
        else if (m_bFireState[ELEVATOR_CELL_NUMBER - 2])
        {
        }
        if (m_bFireState[STAIRS_CELL_NUMBER - 1])
        {
        }

        // if (m_bFireState[ELEVATOR_CELL_NUMBER - 1] == 1) //电梯房左侧
        // {
        //     (this + 1)->m_bFireState[ELEVATOR_CELL_NUMBER - 1] = 1; // warning::: must using continuous address
        // }
        // if (m_bFireState[STAIRS_CELL_NUMBER - 1] == 1)
        // {
        //     (this + 1)->m_bFireState[STAIRS_CELL_NUMBER - 1] = 1;
        // }
    }
}
void Floor::FireBoom()
{
    srand(time(nullptr));
    for (int i = 0; i < 2; i++)
    {
        int FireCellNum = rand() % ONE_FLOOR_CELL_X_NUMBER + 1; // 随机出现着火位置
        m_bFireState[FireCellNum] = 1;
    }
    FloorUpdate();
}
void Floor::FireProduceSmog(float fTimeDelta)
{
    static float CurTime = FIRE_PRODUCE_SMOG_TIME;
    CurTime -= fTimeDelta;
    if (CurTime < 1e-6)
    {
        CurTime = FIRE_PRODUCE_SMOG_TIME;
        for (int i = 0; i < ONE_FLOOR_CELL_X_NUMBER; i++)
        {
            if (m_bFireState[i] == 1)
            {
                m_bSmogState[0][i] = true;
            }
        }
        FloorUpdate();
    }
}
void Floor::FloorUpdate()
{
    m_pFloor->SetSpritePosition(m_PFloorPoi.X, m_PFloorPoi.Y);

    // 更新火焰
    for (int i = 0; i < ONE_FLOOR_CELL_X_NUMBER; i++)
    {
        if (m_bFireState[i] == 1)
        {
            m_pFire[i]->SetSpritePosition(m_PFloorPoi.X - fabs(FIRE_START_X - FLOOR_START_X) + i * FLOOR_CELL_X, m_PFloorPoi.Y + fabs(FIRE_START_Y - FLOOR_START_Y));
        }
    }

    // 更新烟雾
    for (int j = 0; j < ONE_FLOOR_CELL_Y_NUMBER - 1; j++)
    {
        for (int i = 0; i < ONE_FLOOR_CELL_X_NUMBER; i++)
        {
            if (m_bSmogState[j][i] == 1)
            {
                m_pSmog[j][i]->SetSpritePosition(m_PFloorPoi.X - fabs(SMOG_START_X - FLOOR_START_X) + i * FLOOR_CELL_X, m_PFloorPoi.Y - j * FLOOR_CELL_Y + fabs(SMOG_START_Y - FLOOR_START_Y));
            }
        }
    }
}

void Floor::FireDiffusionX(float fTimeDelta)
{
    static float CurTime = FIRE_DIFFUSION_X_TIME;
    CurTime -= fTimeDelta;

    if (CurTime < 1e-6)
    {
        bool tmp_FireState[ONE_FLOOR_CELL_X_NUMBER] = {0}; // 记录这次火焰传播后的数据
        CurTime = FIRE_DIFFUSION_X_TIME;
        // 判断中间单元格的扩散，防越界
        for (int i = 1; i < ONE_FLOOR_CELL_X_NUMBER - 1; i++)
        {
            if (m_bFireState[i] == true)
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
        if (m_bFireState[ONE_FLOOR_CELL_X_NUMBER - 1] == true)
        {
            tmp_FireState[ONE_FLOOR_CELL_X_NUMBER - 2] = 1;
        }

        // 对现状态进行更新
        for (int i = 0; i < ONE_FLOOR_CELL_X_NUMBER; i++)
        {
            m_bFireState[i] = tmp_FireState[i];
        }
        FloorUpdate();
    }
}

void Floor::SmogDiffusionX(float fTimeDelta)
{
    static float CurTime = SMOG_DIFFUSION_X_TIME;
    CurTime -= fTimeDelta;

    if (CurTime < 1e-6)
    {
        bool tmp_SmogState[ONE_FLOOR_CELL_Y_NUMBER - 1][ONE_FLOOR_CELL_X_NUMBER] = {};
        CurTime = SMOG_DIFFUSION_X_TIME;

        for (int j = 0; j < ONE_FLOOR_CELL_Y_NUMBER - 1; j++) // 纵向
        {
            for (int i = 1; i < ONE_FLOOR_CELL_X_NUMBER - 1; i++) // 横向 中间
            {
                if (m_bSmogState[j][i] == true)
                {
                    tmp_SmogState[j][i - 1] = true;
                    tmp_SmogState[j][i + 1] = true;
                    tmp_SmogState[j][i] = true;
                }
                if (m_bSmogState[0][i] == true)
                {
                    tmp_SmogState[1][i] = true;
                }
            }
            // 两侧 横向
            if (m_bSmogState[j][0] == true)
            {
                tmp_SmogState[j][1] = 1;
            }
            if (m_bSmogState[j][ONE_FLOOR_CELL_X_NUMBER - 1] == true)
            {
                tmp_SmogState[j][ONE_FLOOR_CELL_X_NUMBER - 2] = 1;
            }

            // 两侧 纵向
            if (m_bSmogState[0][0] == true)
            {
                tmp_SmogState[1][0] = 1;
            }
            if (m_bSmogState[0][ONE_FLOOR_CELL_X_NUMBER - 1] == true)
            {
                tmp_SmogState[1][ONE_FLOOR_CELL_X_NUMBER - 1] = 1;
            }
        }

        // 更新烟雾状态
        for (int j = 0; j < ONE_FLOOR_CELL_Y_NUMBER - 1; j++)
        {
            for (int i = 0; i < ONE_FLOOR_CELL_X_NUMBER; i++)
            {
                if (tmp_SmogState[j][i] == 1)
                    m_bSmogState[j][i] = tmp_SmogState[j][i];
            }
        }

        FloorUpdate();
    }
}
