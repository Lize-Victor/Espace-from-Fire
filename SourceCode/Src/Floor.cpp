#include "Floor.h"
#include <random>
#include <cmath>
#include <ctime>
#include <vector>
#include <cstring>

using std::vector;

extern vector<Floor *> g_Floor;
bool Floor::m_bDoorState = 0;
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
    CurTime_Fire_X = FIRE_DIFFUSION_X_TIME;
    CurTime_Fire_Y = FIRE_DIFFUSION_Y_TIME;
    CurTime_Smog_X = SMOG_DIFFUSION_X_TIME;
    CurTime_Smog_Produce = FIRE_PRODUCE_SMOG_TIME;
    for (int j = 0; j < ONE_FLOOR_CELL_Y_NUMBER - 1; j++)
    {
        for (int i = 0; i < ONE_FLOOR_CELL_X_NUMBER; i++)
        {
            m_pSmog[j][i] = nullptr;
            m_bSmogState[j][i] = 0;
        }
    }

    for (int j = 0; j < 2; j++)
    {
        for (int i = 0; i < 4; i++)
        {
            m_pFireY[j][i] = nullptr;
            m_bFireStateY[j][i] = 0;
        }
    }

    m_pDoor = nullptr;
    m_bDoorState = 0;

    m_pFloorNum = nullptr;

    m_iPropNum = 0;
}
void Floor::SetDoorVisble(bool tmp_State)
{
    m_pDoor->SetSpriteVisible(tmp_State);
}
void Floor::FloorInit(int iFloorNum)
{
    char *destName = CSystem::MakeSpriteName("Floor", iFloorNum);
    m_pFloor = new CSprite(destName);
    m_pFloor->CloneSprite(FLOOR_API_NAME);
    m_PFloorPoi.X = FLOOR_START_X;
    m_PFloorPoi.Y = FLOOR_START_Y - (iFloorNum - 1) * FLOOR_Y;
    m_iFloorNum = iFloorNum;

    // 初始化门
    char *destNameDoor = CSystem::MakeSpriteName("Floor", iFloorNum);
    destNameDoor = strcat(destNameDoor, "-Door");
    m_pDoor = new CSprite(destNameDoor);
    m_pDoor->CloneSprite(DOOR_API_NAME);

    CSprite *tmp_pDoor;
    tmp_pDoor = new CSprite(DOOR_API_NAME);
    tmp_pDoor->SetSpriteVisible(false);
    m_pDoor->SetSpriteVisible(false);
    srand(time(nullptr));
    m_bDoorState = rand() % 2;

    // 初始化楼层号（文字精灵）
    char *destNameFloorNum = CSystem::MakeSpriteName("Floor", iFloorNum);
    destNameFloorNum = strcat(destNameFloorNum, "-FloorNum");
    m_pFloorNum = new CTextSprite(destNameFloorNum);
    m_pFloorNum->CloneSprite(FLOORNUM_API_NAME);
    m_pFloorNum->SetTextValue(iFloorNum);
    m_pFloorNum->SetSpriteVisible(false);
    CTextSprite *tmp_pFloorNum;
    tmp_pFloorNum = new CTextSprite(FLOORNUM_API_NAME);
    tmp_pFloorNum->SetSpriteVisible(false);

    // 随机刷出道具
    srand(time(nullptr));
    m_iPropNum = rand() % 5 + 1;
    FloorUpdate();
}

void Floor::FireInit()
{
    // 初始化横向火焰
    for (int i = 0; i < ONE_FLOOR_CELL_X_NUMBER; i++)
    {
        char *destNameF = CSystem::MakeSpriteName("Floor", m_iFloorNum);
        destNameF = strcat(destNameF, "-FireX");
        char *destName = CSystem::MakeSpriteName(destNameF, i);
        m_pFire[i] = new CAnimateSprite(destName);
        m_pFire[i]->CloneSprite(FIRE_API_NAME);
    }

    // 初始化纵向火焰
    for (int j = 0; j < 2; j++)
    {
        char *destNameF = CSystem::MakeSpriteName("Floor", m_iFloorNum);
        destNameF = strcat(destNameF, "-FireY");
        char *destName = CSystem::MakeSpriteName(destNameF, j);
        for (int i = 0; i < 3; i++)
        {
            char *destName1 = CSystem::MakeSpriteName(destName, i);
            m_pFireY[j][i] = new CAnimateSprite(destName1);
            m_pFireY[j][i]->CloneSprite(FIRE_API_NAME);
        }
    }
}

void Floor::SmogInit()
{
    for (int j = 0; j < ONE_FLOOR_CELL_Y_NUMBER - 1; j++)
    {
        for (int i = 0; i < ONE_FLOOR_CELL_X_NUMBER; i++)
        {
            char *destName = CSystem::MakeSpriteName("Floor", m_iFloorNum);
            destName = strcat(destName, "-Smog");
            destName = CSystem::MakeSpriteName(destName, j);
            destName = CSystem::MakeSpriteName(destName, i);
            m_pSmog[j][i] = new CAnimateSprite(destName);
            m_pSmog[j][i]->CloneSprite(SMOG_API_NAME);

            m_pSmog[j][i]->SetSpriteCollisionSend(true);
        }
    }
}
void Floor::FireDiffusionY(float fTimeDelta)
{
    CurTime_Fire_Y -= fTimeDelta;
    if (CurTime_Fire_Y < 1e-6)
    {
        CurTime_Fire_Y = FIRE_DIFFUSION_Y_TIME;

        bool tmp_FireStateY[2][3] = {};
        bool tmp_FireState[ONE_FLOOR_CELL_X_NUMBER] = {};

        for (int i = 0; i < ONE_FLOOR_CELL_X_NUMBER; i++)
        {
            tmp_FireState[i] = m_bFireState[i];
        }
        for (int j = 0; j < 2; j++)
        {
            for (int i = 0; i < 3; i++)
            {
                tmp_FireStateY[j][i] = m_bFireStateY[j][i];
            }
        }

        // 向上层传播
        for (int i = 0; i < 3; i++)
        {
            if (GetFloorNum() < 9)
            {
                if (tmp_FireStateY[1][i] == 1 && i < 2)
                {
                    g_Floor[this->GetFloorNum()]->m_bFireState[ELEVATOR_CELL_NUMBER - 1 + i] = 1; // warning::: must using continuous address
                }
                if (tmp_FireStateY[1][i] == 1 && i == 2)
                {
                    g_Floor[this->GetFloorNum()]->m_bFireState[STAIRS_CELL_NUMBER - 1] = 1;
                }
                g_Floor[this->GetFloorNum()]->FloorUpdate();
            }
        }

        // j = 1
        if (tmp_FireStateY[0][0])
        {
            m_bFireStateY[1][0] = 1;
        }
        if (tmp_FireStateY[0][1])
        {
            m_bFireStateY[1][1] = 1;
        }
        if (tmp_FireStateY[0][2])
        {
            m_bFireStateY[1][2] = 1;
        }

        // j = 0
        if (tmp_FireState[ELEVATOR_CELL_NUMBER - 1]) // i = 0
        {
            m_bFireStateY[0][0] = 1;
        }
        if (tmp_FireState[ELEVATOR_CELL_NUMBER]) // i = 1
        {
            m_bFireStateY[0][1] = 1;
        }
        if (tmp_FireState[STAIRS_CELL_NUMBER - 1]) // i = 2
        {
            m_bFireStateY[0][2] = 1;
        }

        // 向下层传播
        for (int i = 0; i < 3; i++)
        {
            if (tmp_FireStateY[1][i] == 1)
            {
                m_bFireStateY[0][i] = 1;
            }
        }

        if (tmp_FireStateY[0][0])
        {
            m_bFireState[ELEVATOR_CELL_NUMBER - 1] = 1;
        }
        if (tmp_FireStateY[0][1])
        {
            m_bFireState[ELEVATOR_CELL_NUMBER] = 1;
        }
        if (tmp_FireStateY[0][2])
        {
            m_bFireState[STAIRS_CELL_NUMBER - 1] = 1;
        }

        if (GetFloorNum() > 1)
        {
            if (tmp_FireState[ELEVATOR_CELL_NUMBER - 1]) // i = 0
            {
                g_Floor[this->GetFloorNum() - 2]->m_bFireStateY[1][0] = 1;
            }
            if (tmp_FireState[ELEVATOR_CELL_NUMBER]) // i = 1
            {
                g_Floor[this->GetFloorNum() - 2]->m_bFireStateY[1][1] = 1;
            }
            if (tmp_FireState[STAIRS_CELL_NUMBER - 1]) // i = 2
            {
                g_Floor[this->GetFloorNum() - 2]->m_bFireStateY[1][2] = 1;
            }
            g_Floor[this->GetFloorNum() - 2]->FloorUpdate();
        }

        FloorUpdate();
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
    CurTime_Smog_Produce -= fTimeDelta;
    if (CurTime_Smog_Produce < 1e-6)
    {
        CurTime_Smog_Produce = FIRE_PRODUCE_SMOG_TIME;
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
void Floor::SmogWarningInit()
{
    char *destName = CSystem::MakeSpriteName("Floor", m_iFloorNum);
    destName = strcat(destName, "-SmogWarning");
    m_pSmogWarning = new CAnimateSprite(destName);
    m_pSmogWarning->CloneSprite(SMOGWARNING_API_NAME);

    m_pSmogWarning->SetSpritePosition(SMOGWARNING_START_X, SMOGWARNING_START_Y - (m_iFloorNum - 1) * FLOOR_Y);
    m_pSmogWarning->AnimateSpritePlayAnimation("SmogWarningAnimation1", 1);
    m_pSmogWarning->SetSpriteCollisionReceive(true);
}
void Floor::SmogWarningBing()
{
    m_pSmog[1][FLOOR_HEIGHT_NUM - 2]->SetSpriteVisible(false);
    m_pSmogWarning->AnimateSpritePlayAnimation("SmogWarningAnimation4", 1);
}
void Floor::ExtinguisherOutFire(Floor *tmp_Floor)
{
    for (int i = 0; i < FLOOR_CELL_X; i++)
    {
        m_bFireState[i] = 0;
    }
    for (int j = 0; j < 2; j++)
    {
        for (int i = 0; i < 3; i++)
        {
            m_bFireStateY[j][i] = 0;
        }
    }

    FloorUpdate();
}
void Floor::FloorUpdate()
{
    m_pFloor->SetSpritePosition(m_PFloorPoi.X, m_PFloorPoi.Y);

    // 更新横向火焰
    for (int i = 0; i < ONE_FLOOR_CELL_X_NUMBER; i++)
    {
        if (m_bFireState[i] == 1)
        {
            m_pFire[i]->SetSpritePosition(m_PFloorPoi.X - fabs(FIRE_START_X - FLOOR_START_X) + i * FLOOR_CELL_X, m_PFloorPoi.Y + fabs(FIRE_START_Y - FLOOR_START_Y));
        }
    }
    // 更新竖向传播的火焰
    for (int j = 0; j < 2; j++)
    {
        for (int i = 0; i < 3; i++)
        {
            if (m_bFireStateY[j][i] && i < 2)
            {
                m_pSmog[j][ELEVATOR_CELL_NUMBER - 1 + i]->SetSpriteVisible(false);
                m_pFireY[j][i]->SetSpritePosition(m_PFloorPoi.X - fabs(SMOG_START_X - FLOOR_START_X) + (i + ELEVATOR_CELL_NUMBER - 1) * FLOOR_CELL_X, m_PFloorPoi.Y - (j + 1) * FLOOR_CELL_Y + fabs(SMOG_START_Y - FLOOR_START_Y) + 0.8);
            }
            if (m_bFireStateY[j][i] && i == 2)
            {
                m_pSmog[j][STAIRS_CELL_NUMBER - 1]->SetSpriteVisible(false);
                m_pFireY[j][i]->SetSpritePosition(m_PFloorPoi.X - fabs(SMOG_START_X - FLOOR_START_X) + (STAIRS_CELL_NUMBER - 1) * FLOOR_CELL_X, m_PFloorPoi.Y - (j + 1) * FLOOR_CELL_Y + fabs(SMOG_START_Y - FLOOR_START_Y) + 0.8);
            }
        }
    }

    // 更新烟雾
    for (int j = 0; j < ONE_FLOOR_CELL_Y_NUMBER - 1; j++)
    {
        for (int i = 0; i < ONE_FLOOR_CELL_X_NUMBER; i++)
        {
            if (m_bSmogState[j][i] == 1)
            {
                m_pSmog[j][i]->SetSpritePosition(m_PFloorPoi.X - fabs(SMOG_START_X - FLOOR_START_X) + i * FLOOR_CELL_X, m_PFloorPoi.Y - (j + 1) * FLOOR_CELL_Y + fabs(SMOG_START_Y - FLOOR_START_Y) + 0.8);
            }
        }
    }
}
void Floor::FireDiffusionX(float fTimeDelta)
{
    CurTime_Fire_X -= fTimeDelta;
    if (CurTime_Fire_X < 1e-6)
    {
        bool tmp_FireState[ONE_FLOOR_CELL_X_NUMBER] = {0}; // 记录这次火焰传播后的数据
        CurTime_Fire_X = FIRE_DIFFUSION_X_TIME;
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
    CurTime_Smog_X -= fTimeDelta;
    if (CurTime_Smog_X < 1e-6)
    {
        bool tmp_SmogState[ONE_FLOOR_CELL_Y_NUMBER - 1][ONE_FLOOR_CELL_X_NUMBER] = {};
        CurTime_Smog_X = SMOG_DIFFUSION_X_TIME;

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
