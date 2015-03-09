#ifndef __BlendAddTest_H__
#define __BlendAddTest_H__

#include "cocos2d.h"
#include "2d/CCDrawNode.h"
#include "DBCCRenderHeaders.h"

USING_NS_CC;

class BlendAddTest : public Layer
{
public:

    virtual bool init() override;
    
    // implement the "static create()" method manually
    CREATE_FUNC(BlendAddTest);

	dragonBones::DBCCArmatureNode *_armature;

};

#endif // __BOUNDING_BOX_SCENE_H__
