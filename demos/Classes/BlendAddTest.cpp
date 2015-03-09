#include "BlendAddTest.h"

USING_NS_CC;

using namespace dragonBones;


// on "init" you need to initialize your instance
bool BlendAddTest::init()
{
    //////////////////////////////
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    auto origin = Director::getInstance()->getVisibleOrigin();

	// factory
    
 	DBCCFactory::getInstance()->loadDragonBonesData("armatures/A/skeleton.xml");
 	DBCCFactory::getInstance()->loadTextureAtlas("armatures/A/texture.xml");
	// armature
	//auto armature = (dragonBones::DBCCArmature *)(DBCCFactory::getInstance()->buildArmature("main", "xiahoudun"));
    auto armature = DBCCFactory::getInstance()->buildArmature("abc", "A");
	_armature = dragonBones::DBCCArmatureNode::create(armature);

 	_armature->getAnimation()->gotoAndPlay("Atk");
    //_armature->update(0);
	_armature->setPosition(480.f, 200.f);
	this->addChild(_armature);
	// armature event
	// update

    return Layer::init();
}

