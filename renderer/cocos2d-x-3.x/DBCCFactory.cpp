#include "DBCCFactory.h"
#include "DBCCEventDispatcher.h"
#include "DBCCTextureAtlas.h"
#include "DBCCArmature.h"
#include "DBCCSlot.h"
#include "cocos2d.h"

NAME_SPACE_DRAGON_BONES_BEGIN

DBCCFactory::DBCCFactory() {}
DBCCFactory::~DBCCFactory() {}

void DBCCFactory::loadSkeleton(const String &skeletonFilePath, const String &name)
{
    if (getSkeletonData(name))
    {
        return;
    }
    auto data = cocos2d::FileUtils::getInstance()->getDataFromFile(skeletonFilePath);
    // 使用XML解析器载入skeleton的xml
    dragonBones::XMLDocument doc;
    doc.Parse(reinterpret_cast<char *>(data.getBytes()), data.getSize());
    // 解析骨骼动画数据
    dragonBones::XMLDataParser parser;
    SkeletonData *skeleton = parser.parseSkeletonData(doc.RootElement());
    addSkeletonData(skeleton, name);
}

void DBCCFactory::loadTextureAtlas(const String &textureAtlasFile, const String &name)
{
    if (getTextureAtlas(name))
    {
        return;
    }
    auto data = cocos2d::FileUtils::getInstance()->getDataFromFile(textureAtlasFile);
    // 载入皮肤数据
    dragonBones::XMLDocument doc;
    doc.Parse(reinterpret_cast<char *>(data.getBytes()), data.getSize());
    // 解析皮肤数据
    dragonBones::XMLDataParser parser;
    TextureAtlasData *textureAtlasData = parser.parseTextureAtlasData(doc.RootElement());
    DBCCTextureAtlas *textureAtlas = new DBCCTextureAtlas(textureAtlasData);
    //
    int pos = textureAtlasFile.find_last_of("/");
    if (String::npos != pos)
    {
        String base_path = textureAtlasFile.substr(0, pos + 1);
        textureAtlasData->imagePath = base_path + textureAtlasData->imagePath;
    }
    //
    textureAtlas->texture = cocos2d::Director::getInstance()->getTextureCache()->addImage(textureAtlasData->imagePath.c_str());
    addTextureAtlas(textureAtlas, name);
}

void DBCCFactory::refreshTextureAtlasTexture()
{
    for (auto iterator = _textureAtlasMap.begin(); iterator != _textureAtlasMap.end(); ++iterator)
    {
        DBCCTextureAtlas *textureAtlas = static_cast<DBCCTextureAtlas *>(iterator->second);
        const TextureAtlasData *textureAtlasData = textureAtlas->textureAtlasData;
        textureAtlas->texture = cocos2d::Director::getInstance()->getTextureCache()->addImage(textureAtlasData->imagePath.c_str());
    }
}

Armature *DBCCFactory::generateArmature(const ArmatureData *armatureData) const
{
    Animation *animation = new Animation();
    //eventDispatcher
    DBCCEventDispatcher *eventDispatcher = new DBCCEventDispatcher();
    eventDispatcher->eventDispatcher = cocos2d::Director::getInstance()->getEventDispatcher();
    eventDispatcher->eventDispatcher->retain();
    //sprite
    cocos2d::Sprite *display = cocos2d::Sprite::create();
	display->setOpacity(128);
    display->retain();
    Armature *armature = new DBCCArmature((ArmatureData *)(armatureData), animation, eventDispatcher, display);
    return armature;
}

Slot *DBCCFactory::generateSlot(const SlotData *slotData) const
{
    DBCCSlot *dbccSlot = new DBCCSlot((SlotData *)(slotData));
    return dbccSlot;
}

void *DBCCFactory::generateDisplay(const ITextureAtlas *textureAtlas, const String &textureName, const DisplayData *displayData) const
{
    DBCCTextureAtlas *dbccTextureAtlas = (DBCCTextureAtlas *)(textureAtlas);
    if (dbccTextureAtlas)
    {
        TextureData *textureData = dbccTextureAtlas->textureAtlasData->getTextureData(textureName);
        if (textureData)
        {
            if (!dbccTextureAtlas->texture)
            {
                // throw
            }
            float x = textureData->region.x;
            float y = textureData->region.y;
            float width = textureData->region.width;
            float height = textureData->region.height;
            cocos2d::Rect rect(x, y, width, height);
            //sprite
            cocos2d::Sprite *display = cocos2d::Sprite::createWithTexture(dbccTextureAtlas->texture, rect, false);
            display->retain();
            float pivotX = displayData->pivot.x;
            float pivotY = displayData->pivot.y;
            if (textureData->frame)
            {
                pivotX += textureData->frame->x;
                pivotY += textureData->frame->y;
            }
            display->setAnchorPoint(cocos2d::Point(pivotX / width, 1.f - pivotY / height));
            display->setContentSize(cocos2d::Size(width, height));
            return display;
        }
    }
    return nullptr;
}
NAME_SPACE_DRAGON_BONES_END