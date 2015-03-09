#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"
#include "2d/CCDrawNode.h"
#include "DBCCRenderHeaders.h"

USING_NS_CC;

class HelloWorld : public Layer
{
public:

    virtual bool init() override;
	virtual void update(float dt) override;

    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);
    
    // implement the "static create()" method manually
    CREATE_FUNC(HelloWorld);

	void armAnimationHandler(cocos2d::EventCustom *event);

	dragonBones::DBCCArmatureNode* createEffect(std::string dragonbones, std::string armature);

	dragonBones::DBCCArmatureNode *_armature;
	cocos2d::DrawNode *drawnode;
	bool _jump2Wait;
	std::string _curAction;

};

#endif // __HELLOWORLD_SCENE_H__
