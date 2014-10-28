#include "BoundingBoxTest.h"

USING_NS_CC;

using namespace dragonBones;

Scene* BoundingBoxTest::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = BoundingBoxTest::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

void BoundingBoxTest::updateHandler(float passTime)
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
void BoundingBoxTest::demoInit()
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
                                           CC_CALLBACK_1(BoundingBoxTest::menuCloseCallback, this));
    
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
    
    auto label = LabelTTF::create("Hello World", "Arial", 24);
    
    // position the label on the center of the screen
    label->setPosition(origin.x + visibleSize.width/2,
                            origin.y + visibleSize.height - label->getContentSize().height);

    // add the label as a child to this layer
    this->addChild(label, 1);


	// factory
    
 	DBCCFactory::getInstance()->loadDragonBonesData("armatures/xiahoudun/skeleton.xml");
 	DBCCFactory::getInstance()->loadTextureAtlas("armatures/xiahoudun/texture.xml");
 	DBCCFactory::getInstance()->loadDragonBonesData("armatures/Knight/skeleton.xml");
 	DBCCFactory::getInstance()->loadTextureAtlas("armatures/Knight/texture.xml");
	// armature
	//auto armature = (dragonBones::DBCCArmature *)(DBCCFactory::getInstance()->buildArmature("main", "xiahoudun"));
    auto armature = DBCCFactory::getInstance()->buildArmature("knight", "Knight");
	_armature = dragonBones::DBCCArmatureNode::create(armature);

	drawnode = DrawNode::create();
	//_armature->addChild(drawnode, -1);
	_armature->addChild(drawnode);

    auto action1 = DelayTime::create(1);
    auto action2 = CallFunc::create([this]{
        auto xx = DBCCFactory::getInstance()->buildArmature("main", "xiahoudun");
        auto arm = DBCCArmatureNode::create(xx);
        arm->getAnimation()->gotoAndPlay("walk");
        addChild(arm);
        arm->setPosition(500, 40);
    });
    runAction(Sequence::createWithTwoActions(action1, action2));
	
 	_armature->getAnimation()->gotoAndPlay("run");
    //_armature->update(0);
	_armature->setPosition(480.f, 200.f);
	this->addChild(_armature);
	// armature event
	auto movementHandler = std::bind(&BoundingBoxTest::armAnimationHandler, this, std::placeholders::_1);
	auto frameHandler = std::bind(&BoundingBoxTest::armAnimationHandler, this, std::placeholders::_1);
	_armature->getCCEventDispatcher()->addCustomEventListener(dragonBones::EventData::START, movementHandler);
	_armature->getCCEventDispatcher()->addCustomEventListener(dragonBones::EventData::FADE_IN, movementHandler);
	_armature->getCCEventDispatcher()->addCustomEventListener(dragonBones::EventData::COMPLETE, movementHandler);
	_armature->getCCEventDispatcher()->addCustomEventListener(dragonBones::EventData::LOOP_COMPLETE, movementHandler);
	_armature->getCCEventDispatcher()->addCustomEventListener(dragonBones::EventData::ANIMATION_FRAME_EVENT, frameHandler);
	// update

	// key
	cocos2d::EventListenerKeyboard *listener = cocos2d::EventListenerKeyboard::create();
	listener->onKeyPressed = [&](cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event *event){
		log("key pressed code=%d", keyCode);
		switch (keyCode)
		{
		case cocos2d::EventKeyboard::KeyCode::KEY_A:
			//_armature->getAnimation()->gotoAndPlay("wait");
			_armature->getAnimation()->gotoAndPlay("skill1");
			
			break;
		case cocos2d::EventKeyboard::KeyCode::KEY_S:
			_armature->getAnimation()->gotoAndPlay("wait");
			break;
		case cocos2d::EventKeyboard::KeyCode::KEY_D:
			_armature->getAnimation()->gotoAndPlay("atk");
			_curAction = "atk";
			_jump2Wait = true;
			break;
		case cocos2d::EventKeyboard::KeyCode::KEY_F:
			_armature->getAnimation()->gotoAndPlay("beAtk");
			_curAction = "beAtk";
			_jump2Wait = true;
			break;
		case cocos2d::EventKeyboard::KeyCode::KEY_W:
			_armature->getAnimation()->gotoAndPlay("skill3");
			_curAction = "skill3";
			auto node = createEffect("leiyanfentian", "skill_self_1");
			_armature->addChild(node);
			_jump2Wait = true;
			break;
		}
	};
	//listener->onKeyReleased = std::bind(&DemoKnight::keyReleaseHandler, this, std::placeholders::_1, std::placeholders::_2);
	this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);
}

void BoundingBoxTest::armAnimationHandler(cocos2d::EventCustom *event)
{
	dragonBones::EventData *eventData = (dragonBones::EventData *)(event->getUserData());

	switch (eventData->getType())
	{
	case dragonBones::EventData::EventType::START:
		cocos2d::log("animation start: %s %f", eventData->animationState->name.c_str(), utils::gettime());
		break;
	case dragonBones::EventData::EventType::FADE_IN:
		cocos2d::log("animation fade in: %s %f", eventData->animationState->name.c_str(), utils::gettime());
		break;

	case dragonBones::EventData::EventType::COMPLETE:
		cocos2d::log("animation complete: %s  %f", eventData->animationState->name.c_str(), utils::gettime());
		if(_jump2Wait && eventData->animationState->name == _curAction)
		{
			_jump2Wait = false;
			_armature->getAnimation()->gotoAndPlay("wait");
		}
		break;
	case dragonBones::EventData::EventType::LOOP_COMPLETE:
		cocos2d::log("animation loop complete: %s  %f", eventData->animationState->name.c_str(), utils::gettime());
		if(_jump2Wait && eventData->animationState->name == _curAction)
		{
			_jump2Wait = false;
			_armature->getAnimation()->gotoAndPlay("wait");
		}
		break;

	case dragonBones::EventData::EventType::ANIMATION_FRAME_EVENT:
		cocos2d::log("animation frame event: %s %s %f", eventData->animationState->name.c_str(), eventData->frameLabel, utils::gettime());
		break;
	}
}

dragonBones::DBCCArmatureNode* BoundingBoxTest::createEffect(std::string dragonbones, std::string armature)
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


void BoundingBoxTest::menuCloseCallback(Ref* pSender)
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
