#ifndef DRAGONBONES_PARSERS_XML_DATA_PARSER_H
#define DRAGONBONES_PARSERS_XML_DATA_PARSER_H

#include "../DragonBones.h"
#include "BaseDataParser.h"

#include "../3rd/tinyxml2/dbtinyxml2.h"

NAME_SPACE_DRAGON_BONES_BEGIN
class XMLDataParser : public BaseDataParser
{
private:
    static bool getBoolean(const XMLElement &data, const char *key, bool defaultValue);
    static float getNumber(const XMLElement &data, const char *key, float defaultValue, float nanValue);
    
private:
    mutable float _textureScale;
    mutable int _frameRate;
	mutable bool _isGlobalData;
    
public:
    XMLDataParser();
    virtual ~XMLDataParser();
    virtual TextureAtlasData* parseTextureAtlasData(const void *rawTextureAtlasData, float scale = 1.f) const;
    virtual DragonBonesData* parseDragonBonesData(const void *rawDragonBonesData) const;
    
private:
    TextureData* parseTextureData(const XMLElement *textureXML) const;
    
    ArmatureData* parseArmatureData(const XMLElement *armatureXML) const;
    BoneData* parseBoneData(const XMLElement *boneXML) const;
    SkinData* parseSkinData(const XMLElement *skinXML) const;
	SlotData* parseSlotDisplayData(const XMLElement *slotXML) const;
    SlotData* parseSlotData(const XMLElement *slotXML) const;
    DisplayData* parseDisplayData(const XMLElement *displayXML) const;
    AnimationData* parseAnimationData(const XMLElement *animationXML, const ArmatureData *armatureData) const;
    TransformTimeline* parseTransformTimeline(const XMLElement *timelineXML, int duration) const;
	SlotTimeline* parseSlotTimeline(const XMLElement *frameXML, int duration) const;
	SlotFrame* parseSlotFrame(const XMLElement *timelineXML) const;
    Frame* parseMainFrame(const XMLElement *frameXML) const;
    TransformFrame* parseTransformFrame(const XMLElement *frameXML) const;
    
    void parseTimeline(const XMLElement &timelineXML, Timeline &timeline) const;
    void parseFrame(const XMLElement &frameXML, Frame &frame) const;
    void parseTransform(const XMLElement &transformXML, Transform &transform) const;
    void parsePivot(const XMLElement &transformXML, Point &pivot) const;
    void parseColorTransform(const XMLElement &colorTransformXML, ColorTransform &colorTransform) const;
    
private:
    DRAGON_BONES_DISALLOW_COPY_AND_ASSIGN(XMLDataParser);
};
NAME_SPACE_DRAGON_BONES_END
#endif  // DRAGONBONES_PARSERS_XML_DATA_PARSER_H
