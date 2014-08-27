﻿#ifndef __OBJECTS_I_AREA_DATA_H__
#define __OBJECTS_I_AREA_DATA_H__

#include "../DragonBones.h"

NAME_SPACE_DRAGON_BONES_BEGIN
class IAreaData
{
public:
    enum class AreaType {AT_ELLIPSE, AT_RECTANGLE};
    
public:
    AreaType areaType;
    String name;
    
public:
    IAreaData() {}
    IAreaData(const IAreaData &copyData)
    {
        operator=(copyData);
    }
    IAreaData& operator=(const IAreaData &copyData)
    {
        areaType = copyData.areaType;
        name = copyData.name;
        return *this;
    }
    virtual ~IAreaData()
    {
    }
    virtual void dispose() = 0;
};
NAME_SPACE_DRAGON_BONES_END
#endif  // __OBJECTS_I_AREA_DATA_H__