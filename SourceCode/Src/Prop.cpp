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
    switch (tmp_PropNum)
    {
    case 1: // 压力钳
        m_iPropNum = 1;
        m_pProp = new CSprite(PLIERS_API_NAME);
        m_pProp->SetSpritePosition(PLIERS_START_X, PLIERS_START_Y);
        m_pPropInTable = new CSprite(CSystem::MakeSpriteName(PLIERS_API_NAME, 1));
        m_pPropInTable->SetSpriteVisible(false);
        break;
    case 2: // 枕头
        m_iPropNum = 2;
        m_pProp = new CSprite(PILLOW_API_NAME);
        m_pPropInTable = new CSprite(CSystem::MakeSpriteName(PILLOW_API_NAME, 1));
        m_pPropInTable->SetSpriteVisible(false);
        break;
    case 3: // 窗帘
        m_iPropNum = 3;
        m_pProp = new CSprite(CURTAIN_API_NAME);
        m_pProp->SetSpritePosition(CURTAIN_START_X, CURTAIN_START_Y);
        m_pPropInTable = new CSprite(CSystem::MakeSpriteName(CURTAIN_API_NAME, 1));
        m_pPropInTable->SetSpriteVisible(false);
        break;
    case 4: // 毛巾
        m_iPropNum = 4;
        m_pProp = new CSprite(TOWEL_API_NAME);
        m_pProp->SetSpritePosition(TOWEL_START_X, TOWEL_START_Y);
        m_pPropInTable = new CSprite(CSystem::MakeSpriteName(TOWEL_API_NAME, 1));
        m_pPropInTable->SetSpriteVisible(false);
        break;
    case 5: // 灭火器
        m_iPropNum = 5;
        m_pProp = new CSprite(EXTINGUISHER_API_NAME);
        m_pProp->SetSpritePosition(EXTINGUISHER_START_X, EXTINGUISHER_START_Y);
        m_pPropInTable = new CSprite(CSystem::MakeSpriteName(EXTINGUISHER_API_NAME, 1));
        m_pPropInTable->SetSpriteVisible(false);
        break;
    }

    m_pProp->SetSpriteCollisionReceive(true);
}

void prop::IntoPropTable()
{
    m_pProp->SetSpritePosition(1000, -1000);
    m_pPropInTable->SetSpriteVisible(true);
}
