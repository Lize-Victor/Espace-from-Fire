#include "CustomFunction.h"

void FloorMove(float deltaY, vector<Floor *> &l_floor)
{
    for (int i = 0; i < FLOOR_HEIGHT_NUM; i++)
    {
        float tmpX = l_floor[i]->GetFloorPoiX();
        float tmpY = l_floor[i]->GetFloorPoiY();
        l_floor[i]->SetFloorPosition(tmpX,tmpY + deltaY);
        l_floor[i]->FloorUpdate();
    }
}