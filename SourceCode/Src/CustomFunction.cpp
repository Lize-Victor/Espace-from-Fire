#include "CustomFunction.h"

void FloorMove(float deltaY, vector<Floor *> &l_floor)
{
    for (int i = 0; i < 9; i++)
    {
        float tmpX = l_floor[i]->GetFloor()->GetSpritePositionX();
        float tmpY = l_floor[i]->GetFloor()->GetSpritePositionY();
        l_floor[i]->SetFloorPosition(tmpX,tmpY + deltaY);
        l_floor[i]->FloorUpdate();
    }
}