﻿#ifndef DRAGONBONES_PARSERS_BASE_DATA_PARSER_H
#define DRAGONBONES_PARSERS_BASE_DATA_PARSER_H

#include "../DragonBones.h"

// geoms
#include "../geoms/ColorTransform.h"
#include "../geoms/Matrix.h"
#include "../geoms/Point.h"
#include "../geoms/Rectangle.h"
#include "../geoms/Transform.h"

// objects
#include "../objects/Frame.h"
#include "../objects/TransformFrame.h"
#include "../objects/Timeline.h"
#include "../objects/TransformTimeline.h"
#include "../objects/AnimationData.h"
#include "../objects/DisplayData.h"
#include "../objects/SlotData.h"
#include "../objects/SkinData.h"
#include "../objects/BoneData.h"
#include "../objects/ArmatureData.h"
#include "../objects/DragonBonesData.h"
#include "../objects/SlotFrame.h"

// textures
#include "../textures/TextureData.h"
#include "../textures/TextureAtlasData.h"

NAME_SPACE_DRAGON_BONES_BEGIN

class BaseDataParser
{
public:
	BaseDataParser();
	virtual ~BaseDataParser();
	virtual TextureAtlasData *parseTextureAtlasData(const void *rawTextureAtlasData, float scale = 1.f) const = 0;
	virtual DragonBonesData *parseDragonBonesData(const void *rawDragonBonesData) const = 0;

protected:
    static void transformArmatureData(ArmatureData *armatureData);
    static void transformArmatureDataAnimations(ArmatureData *armatureData);
    static void transformAnimationData(AnimationData *animationData, const ArmatureData *armatureData, bool isGlobalData = false);
    static void addHideTimeline(AnimationData *animationData, const ArmatureData *armatureData);
    
private:
    static void setFrameTransform(AnimationData *animationData, const ArmatureData *armatureData, const BoneData *boneData, TransformFrame *frame);
    static void getTimelineTransform(const TransformTimeline *timeline, int position, Transform *retult, bool isGlobal);
    
private:
    DRAGON_BONES_DISALLOW_COPY_AND_ASSIGN(BaseDataParser);
};
NAME_SPACE_DRAGON_BONES_END
#endif  // DRAGONBONES_PARSERS_BASE_DATA_PARSER_H
