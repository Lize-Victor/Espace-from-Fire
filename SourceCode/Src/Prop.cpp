#include "Prop.h"
#include <cstring>

#include "MacroDefinition.h"

prop::prop(const char *destName)
{
    strcpy(m_pPropName, destName);
    m_pProp = new CSprite(destName);
    m_pPropInTable = new CSprite(CSystem::MakeSpriteName(destName, 1));
    m_pPropInTable->SetSpriteVisible(false);
}

// 0: 中间楼层 1: 底层 2: 顶层
void prop::PropInit(int i_floor)
{
    switch (i_floor)
    {
    case 0:
        if (!strcmp(m_pPropName, CURTAIN_API_NAME))
        {
            m_pProp->SetSpritePosition(CURTAIN_START_X, CURTAIN_START_Y);
        }
        else if (!strcmp(m_pPropName, PILLOW_API_NAME))
        {
            m_pProp->SetSpritePosition(PILLOW_START_X, PILLOW_START_Y);
        }
        else if (!strcmp(m_pPropName, PLIERS_API_NAME))
        {
            m_pProp->SetSpritePosition(PLIERS_START_X, PLIERS_START_Y);
        }
        else if (!strcmp(m_pPropName, EXTINGUISHER_API_NAME))
        {
            m_pProp->SetSpritePosition(EXTINGUISHER_START_X, EXTINGUISHER_START_Y);
        }
        break;
    case 1:
        if (!strcmp(m_pPropName, CURTAIN_API_NAME))
        {
            m_pProp->SetSpritePosition(CURTAIN_START_X, CURTAIN_START_Y + FLOOR_Y);
        }
        else if (!strcmp(m_pPropName, PILLOW_API_NAME))
        {
            m_pProp->SetSpritePosition(PILLOW_START_X, PILLOW_START_Y + FLOOR_Y);
        }
        else if (!strcmp(m_pPropName, PLIERS_API_NAME))
        {
            m_pProp->SetSpritePosition(PLIERS_START_X, PLIERS_START_Y + FLOOR_Y);
        }
        else if (!strcmp(m_pPropName, EXTINGUISHER_API_NAME))
        {
            m_pProp->SetSpritePosition(EXTINGUISHER_START_X, EXTINGUISHER_START_Y + FLOOR_Y);
        }
        break;
    case 2:
        if (!strcmp(m_pPropName, CURTAIN_API_NAME))
        {
            m_pProp->SetSpritePosition(CURTAIN_START_X, CURTAIN_START_Y + FLOOR_Y);
        }
        else if (!strcmp(m_pPropName, PILLOW_API_NAME))
        {
            m_pProp->SetSpritePosition(PILLOW_START_X, PILLOW_START_Y + FLOOR_Y);
        }
        else if (!strcmp(m_pPropName, PLIERS_API_NAME))
        {
            m_pProp->SetSpritePosition(PLIERS_START_X, PLIERS_START_Y + FLOOR_Y);
        }
        else if (!strcmp(m_pPropName, EXTINGUISHER_API_NAME))
        {
            m_pProp->SetSpritePosition(EXTINGUISHER_START_X, EXTINGUISHER_START_Y + FLOOR_Y);
        }
        break;
    }

    m_pProp->SetSpriteCollisionReceive(true);
}

void prop::IntoPropTable()
{
    m_pProp->SetSpritePosition(1000, -1000);
    m_pPropInTable->SetSpriteVisible(true);
}
