#include "NestArmatureTest.h"

USING_NS_CC;

using namespace dragonBones;

void NestArmatureTest::update(float passTime)
{
	dragonBones::WorldClock::clock.advanceTime(passTime);
	Rect rect = _armature->getBoundingBox();
	Vec2 vec2s[4];
	vec2s[0].x = rect.getMinX();
	vec2s[0].y = rect.getMinY();
	vec2s[1].x = rect.getMinX();
	vec2s[1].y = rect.getMaxY();
	vec2s[2].x = rect.getMaxX();
	vec2s[2].y = rect.getMaxY();
	vec2s[3].x = rect.getMaxX();
	vec2s[3].y = rect.getMinY();

// 	log("rect = x=%f, y=%f, w=%f, h=%f", rect.origin.x, rect.origin.y, rect.size.width, rect.size.height);
// 	log("rect: left=%f, right=%f, top=%f, bottom=%f", rect.getMinX(), rect.getMaxX(), rect.getMaxY(), rect.getMinY());

	drawnode->clear();
	drawnode->drawPolygon(vec2s, 4, Color4F(), 1, Color4F::RED);

}

// on "init" you need to initialize your instance
bool NestArmatureTest::init()
{
    //////////////////////////////
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    auto origin = Director::getInstance()->getVisibleOrigin();

    /////////////////////////////
    // 2. add a menu item with "X" image, which is clicked to quit the program
    //    you may modify it.

    // add a "close" icon to exit the progress. it's an autorelease object
    


    /////////////////////////////
    // 3. add your codes below...

    // add a label shows "Hello World"
    // create and initialize a label
 
	// factory
    clock_t t = clock();
 	DBCCFactory::getInstance()->loadDragonBonesData("armatures/battleCDEffect/skeleton.xml");
 	DBCCFactory::getInstance()->loadTextureAtlas("armatures/battleCDEffect/texture.xml");

    auto testNode = DBCCFactory::getInstance()->buildArmature("cdEffect", "", "cdEffect", "battleCDEffect", "battleCDEffect");
    auto testNode1 = DBCCArmatureNode::create(testNode);
    testNode->getAnimation()->gotoAndPlay("cdKeep");
    addChild(testNode1);

    
	// armature
	//auto armature = (dragonBones::DBCCArmature *)(DBCCFactory::getInstance()->buildArmature("main", "xiahoudun"));
    auto node = Node::create();
    //node->setScale(0.7f);
    node->setPosition(100, 20);
    
    addChild(node);
    //armatureName, "", animationName, dragonBonesName, dragonBonesName
    auto armature = DBCCFactory::getInstance()->buildArmature("epEffect", "", "epEffect", "battleCDEffect", "battleCDEffect");
	_armature = dragonBones::DBCCArmatureNode::create(armature);
    //_armature->setScale(1.2f);
    

 	_armature->getAnimation()->gotoAndPlay("epChange");
    //_armature->update(0);
	_armature->setPosition(480.f, 200.f);
	node->addChild(_armature);

    _armature->getCCEventDispatcher()->addCustomEventListener(EventData::COMPLETE, CC_CALLBACK_1(NestArmatureTest::evtHandler, this));
    _armature->getCCEventDispatcher()->addCustomEventListener(EventData::LOOP_COMPLETE, CC_CALLBACK_1(NestArmatureTest::evtHandler, this));

    t = clock() - t;
    float seconds = ((float)t)/CLOCKS_PER_SEC;
    log("load skeleton time:%f", seconds);
    return Layer::init();
}

void NestArmatureTest::evtHandler(cocos2d::EventCustom *event)
{
	dragonBones::EventData *eventData = (dragonBones::EventData *)(event->getUserData());

	switch (eventData->getType())
	{
	case dragonBones::EventData::EventType::COMPLETE:
        if (eventData->animationState->name == "epChange")
        {
            eventData->armature->getAnimation()->gotoAndPlay("epKeep", -1, -1, 0);
        }
		break;
	case dragonBones::EventData::EventType::LOOP_COMPLETE:
		break;
	}
}

void NestArmatureTest::menuCloseCallback(Ref* pSender)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WP8) || (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT)
	MessageBox("You pressed the close button. Windows Store Apps do not implement a close button.","Alert");
    return;
#endif

    Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}
