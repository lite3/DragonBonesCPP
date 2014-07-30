#ifndef __DRAGONBONE_DB_UTIL_H__
#define __DRAGONBONE_DB_UTIL_H__

#include <string>

namespace dragonBones
{
    class DBUtil
    {
    public:
        static void loadArmature(const std::string &skeletonName, const std::string &armatureName);
        static bool hasArmature(const std::string &skeletonName, const std::string &armatureName = "", const std::string &animationName = "");
    };
};
#endif // __DRAGONBONE_DB_UTIL_H__
