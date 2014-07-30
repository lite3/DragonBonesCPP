
#include "DBUtil.h"
#include "renderer/Cocos2dxFactory.h"
#include "objects/SkeletonData.h"

namespace dragonBones
{
    void DBUtil::loadArmature(const std::string &skeletonXMLFile, const std::string &textureXMLFile)
    {
        dragonBones::Cocos2dxFactory *fac = dragonBones::Cocos2dxFactory::getInstance();
        fac->loadSkeletonFile(skeletonXMLFile);
        fac->loadTextureAtlasFile(textureXMLFile);
    }

    bool DBUtil::hasArmature(const std::string &skeletonName, const std::string &armatureName, const std::string &animationName)
    {
        auto factory = Cocos2dxFactory::getInstance();
        auto data = factory->getSkeletonData(skeletonName);
        if(data)
        {
            if (armatureName.empty())
            {
                return true;
            }
            
            return data->getArmatureData(armatureName);
        }
        
        return false;
    }

};
