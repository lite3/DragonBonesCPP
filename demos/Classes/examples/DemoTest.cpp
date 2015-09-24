#include "DemoTest.h"

USING_NS_DB;

DemoTest::DemoTest()
: _armatureNode(nullptr)
{
}

DemoTest::~DemoTest()
{
    _armatureNode = nullptr;
}

std::string DemoTest::title()
{
    return "TestArmature";
}

std::string DemoTest::subtitle()
{
    return "";
}

void DemoTest::addInteraction()
{

}

void DemoTest::demoInit()
{
    // factory
    DBCCFactory::getInstance()->loadDragonBonesData("armatures/DragonBoy/skeleton.json", "Dragon");
    DBCCFactory::getInstance()->loadTextureAtlas("armatures/DragonBoy/texture.json", "Dragon");
    // armature
    _armatureNode = DBCCFactory::getInstance()->buildArmatureNode("Dragon");
	_armatureNode->setPosition(VisibleRect::center());
	_armatureNode->setScale(0.4f);
    this->addChild(_armatureNode);
	

	// get animations
	std::vector<std::string> animationList = _armatureNode->getAnimation()->getAnimationList();
	float posY = 50;
	int size = animationList.size();
	for (int i =0; i < size; i++)
	{
		Button* button = Button::create("button.png", "button.png");
		button->setTitleText(animationList[i]);
		button->setTitleFontSize(40);
		button->setScale(0.5);
		button->setPosition(Vec2(200, posY + 30 * i));
		button->addTouchEventListener(CC_CALLBACK_2(DemoTest::touchEvent, this));
		this->addChild(button, 0, i);
	}

	// other
	static bool isLoaded = false;
	if (!isLoaded)
	{
		Button* button = Button::create("button.png", "button.png");
		button->setTitleText("-(2x)");
		button->setTitleFontSize(40);
		button->setScale(0.5);
		button->setPosition(Vec2(1136/2  - 70, 150));
		button->addTouchEventListener(CC_CALLBACK_2(DemoTest::touchEvent, this));
		this->addChild(button, 0, 101);

		button = Button::create("button.png", "button.png");
		button->setTitleText("+(2x)");
		button->setTitleFontSize(40);
		button->setScale(0.5);
		button->setPosition(Vec2(1136/2 + 70, 150));
		button->addTouchEventListener(CC_CALLBACK_2(DemoTest::touchEvent, this));
		this->addChild(button, 0, 102);

		button = Button::create("button.png", "button.png");
		button->setTitleText("Pause");
		button->setTitleFontSize(40);
		button->setScale(0.5);
		button->setPosition(Vec2(1136/2  - 70, 100));
		button->addTouchEventListener(CC_CALLBACK_2(DemoTest::touchEvent, this));
		this->addChild(button, 0, 201);

		button = Button::create("button.png", "button.png");
		button->setTitleText("Resume");
		button->setTitleFontSize(40);
		button->setScale(0.5);
		button->setPosition(Vec2(1136/2 + 70, 100));
		button->addTouchEventListener(CC_CALLBACK_2(DemoTest::touchEvent, this));
		this->addChild(button, 0, 202);
	}
}

void DemoTest::touchEvent( Ref *pSender, Widget::TouchEventType type )
{
	Button* item = (Button*)pSender;
	switch (type)
	{
	case Widget::TouchEventType::BEGAN:
		item->setScale(1);
		break;

	case Widget::TouchEventType::MOVED:
		item->setScale(0.5);
		break;

	case Widget::TouchEventType::ENDED:
		{
			item->setScale(0.5);
			switch (item->getTag())
			{
			case 101:
				{
					// ¼õËÙ
					float orignSpeed = _armatureNode->getAnimation()->getTimeScale();
					_armatureNode->getAnimation()->setTimeScale(orignSpeed * 0.5f);
				}
				break;
			case 102:
				{
					// ¼ÓËÙ 
					float orignSpeed = _armatureNode->getAnimation()->getTimeScale();
					_armatureNode->getAnimation()->setTimeScale(orignSpeed * 2.f);
				}
				break;
			case 201:
				{
					// ÔÝÍ£
					_armatureNode->getAnimation()->stop();
				}
				break;
			case 202:
				{
					_armatureNode->getAnimation()->play();
				}
				break;
			default:
				{
					if (_armatureNode)
					{
						_armatureNode->getAnimation()->gotoAndPlay(item->getTitleText(), 0);
					}
				}
				break;
			}
		}
		break;

	case Widget::TouchEventType::CANCELED:
		item->setScale(0.5);
		break;

	default:
		break;
	}
}
