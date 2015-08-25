#ifndef CORE_ARMATURE_H
#define CORE_ARMATURE_H

#include "../DragonBones.h"
#include "../animation/IAnimatable.h"
#include "geoms/Rectangle.h"

NAME_SPACE_DRAGON_BONES_BEGIN

class Frame;
class EventData;
class IEventDispatcher;
class DBObject;
class DragonBonesData;
class ArmatureData;
class Bone;
class Slot;
class Animation;
class AnimationState;

class Armature : public IAnimatable
{
    friend class Bone;
    friend class Slot;
	friend class Animation;
	friend class AnimationState;

public:
    std::string name;
    void *userData;
    
protected:
    bool _needUpdate;
    bool _slotsZOrderChanged;
    bool _delayDispose;
    bool _lockDispose;
    bool _isInheritAnimation;
    
    std::vector<Bone*> _boneList;
    std::vector<Slot*> _slotList;
    std::vector<EventData*> _eventDataList;
	//std::vector<Skin*> _skinLists;

	DragonBonesData *_dragonBonesData;
    ArmatureData *_armatureData;
    Animation *_animation;
    IEventDispatcher *_eventDispatcher;
    void *_display;
    
public:
	static IEventDispatcher *soundEventDispatcher;

	Armature(ArmatureData *armatureData, Animation *animation, IEventDispatcher *eventDispatcher, void *display);
	virtual ~Armature();
	virtual void dispose();

    virtual Rectangle getBoundingBox() = 0;
	virtual const std::vector<Bone*>& getBones() const;
    virtual const std::vector<Slot*>& getSlots() const; 
    virtual const ArmatureData* getArmatureData() const;
	ArmatureData* getArmatureData() { return _armatureData; }

    virtual Animation* getAnimation() const;
    virtual void* getDisplay() const;
    virtual IEventDispatcher* getEventDispatcher() const;
    
public:
    virtual bool isInheritAnimation() const { return _isInheritAnimation; };
    virtual void setInheritAnimation(bool b) { _isInheritAnimation = b; };
    virtual Bone* getBone(const std::string &boneName) const;
    virtual Bone* getBoneByDisplay(const void *display) const;
    virtual void addBone(Bone *bone);
    virtual void addBone(Bone *bone, const std::string &parentBoneName, bool updateLater = false);
    virtual void removeBone(Bone *bone, bool updateLater = false);
    virtual Bone* removeBone(const std::string &boneName);
    
    virtual Slot* getSlot(const std::string &slotName) const;
    virtual Slot* getSlotByDisplay(const void *display) const;
    virtual void addSlot(Slot *slot, const std::string &parentBoneName);
    virtual void removeSlot(Slot *slot);
    virtual Slot* removeSlotByName(const std::string &slotName);
    //virtual void replaceSlot(const std::string &boneName, const std::string &oldSlotName, Slot* newSlot);
    virtual void sortSlotsByZOrder() {}
    
    //virtual void invalidUpdate();
    //virtual void invalidUpdate(const std::string &boneName);

	void invalidUpdate(const std::string &boneName = "");
    virtual void advanceTime(float passedTime) override;

	//virtual void addSkinList(const std::string &skinName, Skin *list);
	//virtual void changeSkin(const std::string &skinName);
	//virtual Skin* getSkin(const std::string &skinName) const;

	virtual void resetAnimation();
    void updateSlotsZOrder();
	void updateAnimationAfterBoneListChanged(bool ifNeedSortBoneList = true);

protected:
    virtual void addObject(DBObject *object);
    virtual void removeObject(DBObject *object);
	
    virtual void sortBonesList();
    static bool sortSlot(const Slot *a, const Slot *b);
	
    virtual void arriveAtFrame(Frame *frame, AnimationState *animationState, bool isCross);
	
	void addBoneToBoneList(Bone *bone);
	void removeBoneFromBoneList(Bone *bone);
	void addSlotToSlotList(Slot *slot);
	void removeSlotFromSlotList(Slot *slot);
private:
	static bool sortBone(const std::pair<int, Bone*> &a, const std::pair<int, Bone*> &b);

private:
    DRAGON_BONES_DISALLOW_COPY_AND_ASSIGN(Armature);
};
NAME_SPACE_DRAGON_BONES_END
#endif  // CORE_ARMATURE_H
