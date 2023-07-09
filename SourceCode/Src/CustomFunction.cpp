#include "CustomFunction.h"
#include <ctime>
#include <random>

void FloorMove(int tmp_iFloorNum, vector<Floor *> &l_floor)
{
    for (int i = 0; i < FLOOR_HEIGHT_NUM; i++)
    {
        float tmpX = l_floor[i]->GetFloorPoiX();
        float tmpY = l_floor[i]->GetFloorPoiY();
        l_floor[i]->SetFloorPosition(tmpX,tmpY + tmp_iFloorNum *FLOOR_Y);
        l_floor[i]->FloorUpdate();
    }
    l_floor[tmp_iFloorNum+1]->SetFloorNumVisble(true);
    l_floor[tmp_iFloorNum+1]->SetDoorVisble();
}


