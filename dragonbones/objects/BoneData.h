﻿#ifndef OBJECTS_BONE_DATA_H
#define OBJECTS_BONE_DATA_H

#include "../DragonBones.h"
#include "../geoms/Transform.h"

NAME_SPACE_DRAGON_BONES_BEGIN
class BoneData
{
public:
    bool inheritScale;
    bool inheritRotation;
    float length;
    
    std::string name;
    std::string parent;
    Transform global;
    Transform transform;
    
public:
    BoneData() :
		inheritScale(false)
		,inheritRotation(false)
		,length(0.f)
		,name("")
		,parent("")
    {}
    BoneData(const BoneData &copyData)
    {
        operator=(copyData);
    }
    BoneData& operator=(const BoneData &copyData)
    {
        dispose();
        inheritScale = copyData.inheritScale;
        inheritRotation = copyData.inheritRotation;
        length = copyData.length;
        name = copyData.name;
        parent = copyData.parent;
        global = copyData.global;
        transform = copyData.transform;
        
        return *this;
    }
    virtual ~BoneData()
    {
        dispose();
    }
    void dispose()
    {
    }
};
NAME_SPACE_DRAGON_BONES_END
#endif  // OBJECTS_BONE_DATA_H
