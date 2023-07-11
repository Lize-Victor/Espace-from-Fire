#include "Prop.h"
#include <cstring>

#include "MacroDefinition.h"

prop::prop()
{
    m_pProp = nullptr;
    m_pPropInTable = nullptr;
    m_iPropNum = 0;
}

void prop::PropInit(int tmp_PropNum)
{
    // 道具栏中的道具初始化
    m_pPropInTable = new CSprite(CSystem::MakeSpriteName(PLIERS_API_NAME, 1));
    m_pPropInTable->SetSpriteVisible(false);

    m_pPropInTable = new CSprite(CSystem::MakeSpriteName(PILLOW_API_NAME, 1));
    m_pPropInTable->SetSpriteVisible(false);

    m_pPropInTable = new CSprite(CSystem::MakeSpriteName(CURTAIN_API_NAME, 1));
    m_pPropInTable->SetSpriteVisible(false);

    m_pPropInTable = new CSprite(CSystem::MakeSpriteName(TOWEL_API_NAME, 1));
    m_pPropInTable->SetSpriteVisible(false);

    m_pPropInTable = new CSprite(CSystem::MakeSpriteName(EXTINGUISHER_API_NAME, 1));
    m_pPropInTable->SetSpriteVisible(false);
    // 地图中道具初始化
    switch (tmp_PropNum)
    {
    case 1: // 压力钳
        m_iPropNum = 1;
        m_pProp = new CSprite(PLIERS_API_NAME);
        m_pProp->SetSpritePosition(PLIERS_START_X, PLIERS_START_Y);
        m_pPropInTable = new CSprite(CSystem::MakeSpriteName(PLIERS_API_NAME, 1));
        break;
    case 2: // 枕头
        m_iPropNum = 2;
        m_pProp = new CSprite(PILLOW_API_NAME);
        m_pProp->SetSpritePosition(PILLOW_START_X, PILLOW_START_Y);
        m_pPropInTable = new CSprite(CSystem::MakeSpriteName(PILLOW_API_NAME, 1));
        break;
    case 3: // 窗帘
        m_iPropNum = 3;
        m_pProp = new CSprite(CURTAIN_API_NAME);
        m_pProp->SetSpritePosition(CURTAIN_START_X, CURTAIN_START_Y);
        m_pPropInTable = new CSprite(CSystem::MakeSpriteName(CURTAIN_API_NAME, 1));
        break;
    case 4: // 毛巾
        m_iPropNum = 4;
        m_pProp = new CSprite(TOWEL_API_NAME);
        m_pProp->SetSpritePosition(TOWEL_START_X, TOWEL_START_Y);
        m_pPropInTable = new CSprite(CSystem::MakeSpriteName(TOWEL_API_NAME, 1));
        break;
    case 5: // 灭火器
        m_iPropNum = 5;
        m_pProp = new CSprite(EXTINGUISHER_API_NAME);
        m_pProp->SetSpritePosition(EXTINGUISHER_START_X, EXTINGUISHER_START_Y);
        m_pPropInTable = new CSprite(CSystem::MakeSpriteName(EXTINGUISHER_API_NAME, 1));
        break;
    }


    m_pProp->SetSpriteCollisionReceive(true);
}

void prop::IntoPropTable()
{
    m_pProp->SetSpritePosition(1000, -1000);
    m_pPropInTable->SetSpriteVisible(true);
}

void prop::OutPropTable(float tmp_PersonPoiX, float tmp_PersonPoiY)
{
    m_pProp->SetSpritePosition(tmp_PersonPoiX,tmp_PersonPoiY);
    m_pPropInTable->SetSpriteVisible(false);
}

int prop::GetPropNumByName(const char *PropName)
{
    if (!strcmp(PropName, PLIERS_API_NAME))
    {
        return 1;
    }
    else if (!strcmp(PropName, PILLOW_API_NAME))
    {
        return 2;
    }
    else if (!strcmp(PropName, CURTAIN_API_NAME))
    {
        return 3;
    }
    else if (!strcmp(PropName, TOWEL_API_NAME))
    {
        return 4;
    }
    else if (!strcmp(PropName, EXTINGUISHER_API_NAME))
    {
        return 5;
    }
    else
        return 0;
}

void prop::PropUpdate(int tmp_PropNum)
{
    m_pProp->SetSpritePosition(1000, -1000); // 将现有道具移出边界

    switch (tmp_PropNum) // 加入新道具
    {
    case 1: // 压力钳
        m_iPropNum = 1;
        m_pProp = new CSprite(PLIERS_API_NAME);
        m_pProp->SetSpritePosition(PLIERS_START_X, PLIERS_START_Y);
        break;
    case 2: // 枕头
        m_iPropNum = 2;
        m_pProp = new CSprite(PILLOW_API_NAME);
        m_pProp->SetSpritePosition(PILLOW_START_X, PILLOW_START_Y);
        break;
    case 3: // 窗帘
        m_iPropNum = 3;
        m_pProp = new CSprite(CURTAIN_API_NAME);
        m_pProp->SetSpritePosition(CURTAIN_START_X, CURTAIN_START_Y);
    case 4: // 毛巾
        m_iPropNum = 4;
        m_pProp = new CSprite(TOWEL_API_NAME);
        m_pProp->SetSpritePosition(TOWEL_START_X, TOWEL_START_Y);
        break;
    case 5: // 灭火器
        m_iPropNum = 5;
        m_pProp = new CSprite(EXTINGUISHER_API_NAME);
        m_pProp->SetSpritePosition(EXTINGUISHER_START_X, EXTINGUISHER_START_Y);
        break;
    }
}
