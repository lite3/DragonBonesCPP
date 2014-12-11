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
    auto closeItem = MenuItemImage::create(
                                           "CloseNormal.png",
                                           "CloseSelected.png",
                                           CC_CALLBACK_1(XMLLoadTest::menuCloseCallback, this));
    
	closeItem->setPosition(origin.x + visibleSize.width - closeItem->getContentSize().width/2 ,
                                origin.y + closeItem->getContentSize().height/2);

    // create menu, it's an autorelease object
    auto menu = Menu::create(closeItem, NULL);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 1);

    auto node = Node::create();
    node->setContentSize(Size(100,200));
    node->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
    node->setPosition(50, 40);
    auto rect = node->getBoundingBox();

    /////////////////////////////
    // 3. add your codes below...

    // add a label shows "Hello World"
    // create and initialize a label
 
	// factory
    clock_t t = clock();
 	DBCCFactory::getInstance()->loadDragonBonesData("armatures/battleCDEffect/skeleton.xml");
 	DBCCFactory::getInstance()->loadTextureAtlas("armatures/battleCDEffect/texture.xml");

    
	// armature
	//auto armature = (dragonBones::DBCCArmature *)(DBCCFactory::getInstance()->buildArmature("main", "xiahoudun"));
    auto armature = DBCCFactory::getInstance()->buildArmature("cdEffect", "battleCDEffect");
	_armature = dragonBones::DBCCArmatureNode::create(armature);
    

 	_armature->getAnimation()->gotoAndPlay("cdKeep");
    //_armature->update(0);
	_armature->setPosition(480.f, 200.f);
	this->addChild(_armature);

    t = clock() - t;
    float seconds = ((float)t)/CLOCKS_PER_SEC;
    log("load skeleton time:%f", seconds);
    return Layer::init();
}

void NestArmatureTest::armAnimationHandler(cocos2d::EventCustom *event)
{
	dragonBones::EventData *eventData = (dragonBones::EventData *)(event->getUserData());

	switch (eventData->getType())
	{
	case dragonBones::EventData::EventType::START:
		cocos2d::log("animation start: %s %f", eventData->animationState->name.c_str());
		break;
	case dragonBones::EventData::EventType::FADE_IN:
		cocos2d::log("animation fade in: %s %f", eventData->animationState->name.c_str());
		break;

	case dragonBones::EventData::EventType::COMPLETE:
		cocos2d::log("animation complete: %s  %f", eventData->animationState->name.c_str());
		if(_jump2Wait && eventData->animationState->name == _curAction)
		{
			_jump2Wait = false;
			_armature->getAnimation()->gotoAndPlay("wait");
		}
		break;
	case dragonBones::EventData::EventType::LOOP_COMPLETE:
		cocos2d::log("animation loop complete: %s  %f", eventData->animationState->name.c_str());
		if(_jump2Wait && eventData->animationState->name == _curAction)
		{
			_jump2Wait = false;
			_armature->getAnimation()->gotoAndPlay("wait");
		}
		break;

	case dragonBones::EventData::EventType::ANIMATION_FRAME_EVENT:
		cocos2d::log("animation frame event: %s %s %f", eventData->animationState->name.c_str(), eventData->frameLabel);
		break;
	}
}

dragonBones::DBCCArmatureNode* NestArmatureTest::createEffect(std::string dragonbones, std::string armature)
{
	auto effect = DBCCFactory::getInstance()->buildArmature(armature, "", "", dragonbones, dragonbones);
	effect->getAnimation()->gotoAndPlay("mv");
	auto node = dragonBones::DBCCArmatureNode::create(effect);
	dragonBones::WorldClock::clock.add(effect);
	auto handler = [](cocos2d::EventCustom *event){
		dragonBones::EventData *eventData = (dragonBones::EventData *)(event->getUserData());
		dragonBones::WorldClock::clock.remove(eventData->armature);
		auto node1 = static_cast<Node*>(eventData->armature->getDisplay());
		//node1->getParent()->removeFromParent();
		node1->setVisible(false);
		eventData->armature->getAnimation()->stop();
	};
	node->getCCEventDispatcher()->addCustomEventListener(dragonBones::EventData::COMPLETE, handler);
	node->getCCEventDispatcher()->addCustomEventListener(dragonBones::EventData::LOOP_COMPLETE, handler);
	return node;
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
