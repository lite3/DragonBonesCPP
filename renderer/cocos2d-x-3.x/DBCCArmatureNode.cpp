#include "DBCCArmatureNode.h"
#include "DBCCEventDispatcher.h"

#if (DRAGON_BONES_ENABLE_LUA == 1)
#include "CCLuaEngine.h"
#endif // DRAGON_BONES_ENABLE_LUA


NAME_SPACE_DRAGON_BONES_BEGIN

DBCCArmatureNode* BCCArmatureNode::create(DBCCArmature *armature)
{
    DBCCArmatureNode *ret = new DBCCArmatureNode();
    
    if (ret && ret->initWithDBCCArmature(armature))
    {
        ret->autorelease();
    }
    else
    {
        CC_SAFE_DELETE(ret);
    }
    
    return ret;
}

bool DBCCArmatureNode::initWithDBCCArmature(DBCCArmature *armature)
{
    if (armature != nullptr)
    {
        _armature = armature;
        addChild(armature->getCCDisplay());
        scheduleUpdate();
        return true;
    }

	return false;
}


DBCCArmatureNode::DBCCArmatureNode()
	:_armature(nullptr)
	,_frameEventHandler(0)
	,_movementEventHandler(0)
{
}
DBCCArmatureNode::~DBCCArmatureNode()
{
#if (DRAGON_BONES_ENABLE_LUA == 1)
	unregisterFrameEventHandler();
	unregisterMovementEventHandler();
#endif // DRAGON_BONES_ENABLE_LUA

    if (_armature)
    {
        _armature->dispose();
        _armature = nullptr;
    }
}

cocos2d::Rect DBCCArmatureNode::getBoundingBox() const
{
    float minx, miny, maxx, maxy = 0;
    bool first = true;
    cocos2d::Rect boundingBox;
    
for (const auto slot : _armature->getSlots())
    {
        if (! slot->getVisible()) { continue; }
        
        auto node = static_cast<cocos2d::Node *>(slot->getDisplay());
        auto r = node->getBoundingBox();
        
        if (first)
        {
            minx = r.getMinX();
            miny = r.getMinY();
            maxx = r.getMaxX();
            maxy = r.getMaxY();
            first = false;
        }
        else
        {
            minx = r.getMinX() < boundingBox.getMinX() ? r.getMinX() : boundingBox.getMinX();
            miny = r.getMinY() < boundingBox.getMinY() ? r.getMinY() : boundingBox.getMinY();
            maxx = r.getMaxX() > boundingBox.getMaxX() ? r.getMaxX() : boundingBox.getMaxX();
            maxy = r.getMaxY() > boundingBox.getMaxY() ? r.getMaxY() : boundingBox.getMaxY();
        }
        
        boundingBox.setRect(minx, miny, maxx - minx, maxy - miny);
    }
    
    auto display = _armature->getCCDisplay();
    return cocos2d::RectApplyTransform(boundingBox, display->getNodeToParentTransform());
}

void DBCCArmatureNode::update(float dt)
{
	retain();
	getArmature()->advanceTime(dt);
	release();
}

///////////////////////////////////////////////////////////////////////
/////////////// for lua
///////////////////////////////////////////////////////////////////////

#if (DRAGON_BONES_ENABLE_LUA == 1)

void DBCCArmatureNode::registerFrameEventHandler(cocos2d::LUA_FUNCTION func)
{
	unregisterFrameEventHandler();
	_frameEventHandler = func;

	auto dispatcher = getCCEventDispatcher();

	auto f = [this](cocos2d::EventCustom *event)
	{
		auto eventData = (dragonBones::EventData *)(event->getUserData());
		int type = (int) eventData->getType();
		std::string movementId = eventData->animationState->name;
		std::string frameLabel = eventData->frameLabel;

		auto stack = cocos2d::LuaEngine::getInstance()->getLuaStack();
		stack->pushObject(this, "db.DBCCArmatureNode");
		stack->pushInt(type);
		stack->pushString(movementId.c_str(), movementId.size());
		stack->pushString(frameLabel.c_str(), frameLabel.size());
		stack->executeFunctionByHandler(_frameEventHandler, 4);
	};

	dispatcher->addCustomEventListener(dragonBones::EventData::ANIMATION_FRAME_EVENT, f);
}

void DBCCArmatureNode::registerMovementEventHandler(cocos2d::LUA_FUNCTION func)
{
	unregisterMovementEventHandler();
	_movementEventHandler = func;

	auto dispatcher = getCCEventDispatcher();

	auto f = [this](cocos2d::EventCustom *event)
	{
		auto eventData = (dragonBones::EventData *)(event->getUserData());
		int type = (int) eventData->getType();
		std::string movementId = eventData->animationState->name;
		std::string frameLabel = eventData->frameLabel;

		auto stack = cocos2d::LuaEngine::getInstance()->getLuaStack();
		stack->pushObject(this, "db.DBCCArmatureNode");
		stack->pushInt(type);
		stack->pushString(movementId.c_str(), movementId.size());
		stack->executeFunctionByHandler(_movementEventHandler, 3);
	};

	dispatcher->addCustomEventListener(dragonBones::EventData::COMPLETE, f);
	dispatcher->addCustomEventListener(dragonBones::EventData::LOOP_COMPLETE, f);
}

void DBCCArmatureNode::unregisterFrameEventHandler()
{
	if (_frameEventHandler != 0)
	{
		cocos2d::LuaEngine::getInstance()->removeScriptHandler(_frameEventHandler);
		_frameEventHandler = 0;
	}
}

void DBCCArmatureNode::unregisterMovementEventHandler()
{
	if (_movementEventHandler != 0)
	{
		cocos2d::LuaEngine::getInstance()->removeScriptHandler(_movementEventHandler);
		_movementEventHandler = 0;
	}
}

#endif // !DRAGON_BONES_ENABLE_LUA


NAME_SPACE_DRAGON_BONES_END