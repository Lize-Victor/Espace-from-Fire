#include "CustomFunction.h"
#include "MacroDefinition.h"
#include <windows.h>
#include <ctime>
#include <random>

void FloorMove(int cur_FloorNum, int tmp_iFloorNum, vector<Floor *> &l_floor)
{

    for (int i = 0; i < FLOOR_HEIGHT_NUM; i++)
    {
        float tmpX = l_floor[i]->GetFloorPoiX();
        float tmpY = l_floor[i]->GetFloorPoiY();
        l_floor[i]->SetFloorPosition(tmpX, tmpY + (tmp_iFloorNum - cur_FloorNum + 2) * FLOOR_Y);
        l_floor[i]->FloorUpdate();
    }
    CSprite *ElevatorRunning = new CSprite("ElevatorRunning");
    ElevatorRunning->SetSpritePosition(75.f,-40.f);
    //Sleep((tmp_iFloorNum - cur_FloorNum + 2) * 1000);
    ElevatorRunning->SetSpritePosition(1000,-1000);
    l_floor[cur_FloorNum - 1]->SetFloorNumVisble(false);
    l_floor[tmp_iFloorNum + 1]->SetFloorNumVisble(true);
    l_floor[tmp_iFloorNum + 1]->SetDoorVisble();
    ElevatorRunning->DeleteSprite();
}

void FireHurt(int &tmp_Blood)
{
    float tmp_deltaTime = CSystem::GetTimeDelta();
    tmp_Blood -= (tmp_deltaTime * FIRE_HURT_COEFFICIENT);
}

void SmogHurt(int &tmp_Blood, int tmp_PropNum)
{
    float tmp_deltaTime = CSystem::GetTimeDelta();

    if (tmp_PropNum == 4)
    {
        tmp_Blood -= (tmp_deltaTime * SMOG_HURT_COEFFICIENT * 0.5);
    }
    else
        tmp_Blood -= (tmp_deltaTime * SMOG_HURT_COEFFICIENT);
}
