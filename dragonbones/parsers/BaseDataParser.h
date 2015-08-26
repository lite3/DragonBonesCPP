#ifndef DRAGONBONES_PARSERS_BASE_DATA_PARSER_H
#define DRAGONBONES_PARSERS_BASE_DATA_PARSER_H

#include "dragonbones/DragonBones.h"

// geoms
#include "dragonbones/geoms/ColorTransform.h"
#include "dragonbones/geoms/Matrix.h"
#include "dragonbones/geoms/Point.h"
#include "dragonbones/geoms/Rectangle.h"
#include "dragonbones/geoms/Transform.h"

// objects
#include "dragonbones/objects/Frame.h"
#include "dragonbones/objects/TransformFrame.h"
#include "dragonbones/objects/Timeline.h"
#include "dragonbones/objects/TransformTimeline.h"
#include "dragonbones/objects/AnimationData.h"
#include "dragonbones/objects/DisplayData.h"
#include "dragonbones/objects/SlotData.h"
#include "dragonbones/objects/SkinData.h"
#include "dragonbones/objects/BoneData.h"
#include "dragonbones/objects/ArmatureData.h"
#include "dragonbones/objects/DragonBonesData.h"
#include "dragonbones/objects/SlotFrame.h"

// textures
#include "dragonbones/textures/TextureData.h"
#include "dragonbones/textures/TextureAtlasData.h"

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
