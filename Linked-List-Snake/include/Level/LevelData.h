#pragma once

#include "Level/LevelNumber.h"
#include "Level/LevelService.h"


namespace Level
{
    struct LevelData
    {
        LevelData(LevelNumber ind)
        {
            level_index = ind;
        }

        LevelNumber level_index;
    };
}