#ifndef CORE_SLOT_H
#define CORE_SLOT_H

#include "DBObject.h"
#include "../DragonBones.h"
#include "../geoms/Rectangle.h"
#include "../geoms/ColorTransform.h"

NAME_SPACE_DRAGON_BONES_BEGIN

class Frame;
class SlotData;
class AnimationState;
class SlotTimelineState;

class Slot : public DBObject
{    
	friend class Armature;
	friend class Bone;
	friend class Animation;
	friend class BaseFactory;
	friend class SlotTimelineState;

protected:
    bool _isShowDisplay;
    bool _isColorChanged;
	int _displayIndex;
    float _originZOrder;
    float _tweenZOrder;
    float _offsetZOrder;
    BlendMode _blendMode;

    ColorTransform _colorTransform;
    
    // <displayOrArmature*, DisplayType>
    std::vector<std::pair<void*, DisplayType>> _displayList;
    
    SlotData *_slotData;
    void *_display;
    Armature *_childArmature;
    
public:
    virtual Rectangle getBoundingBox() = 0;

    virtual int getDisplayIndex() const;
    bool isShowDisplay() const { return _isShowDisplay; }
	bool isColorChanged() const { return _isColorChanged; }

    virtual SlotData* getSlotData() const;
    
    virtual float getZOrder() const;
    virtual void setZOrder(float zorder);
    
    virtual void* getDisplay() const;
    virtual void setDisplay(void *display, const DisplayType displayType = DisplayType::DT_IMAGE, bool disposeExisting = true);
    
    virtual Armature* getChildArmature() const;
    virtual void setChildArmature(Armature *childArmature, bool disposeExisting = true);
    
    virtual const std::vector<std::pair<void*, DisplayType>>& getDisplayList() const;
    virtual void setDisplayList(const std::vector<std::pair<void*, DisplayType>> &displayList, bool disposeExisting = true);
    
    virtual void setVisible(bool vislble) override;
	virtual void updateDisplayColor(int aOffset, int rOffset, int gOffset, int bOffset, float aMultiplier, float rMultiplier, float gMultiplier, float bMultiplier, bool colorChanged = false);

protected:
    virtual void setArmature(Armature *armature) override;
    
public:
    Slot(SlotData *slotData);
    virtual ~Slot();
    virtual void dispose() override;
    
protected:
    virtual void update();
    virtual void changeDisplay(int displayIndex);
    virtual void updateSlotDisplay(bool disposeExisting);
    virtual void updateChildArmatureAnimation();
    virtual void playChildArmatureAnimation();
    virtual void stopChildArmatureAnimation();
    
    virtual int getDisplayZIndex() const = 0;
    virtual void addDisplayToContainer(void *container, int zIndex) = 0;
    virtual void removeDisplayFromContainer() = 0;
    virtual void disposeDisplay() = 0;
    virtual void disposeDisplayList() = 0;
    virtual void updateDisplay(void *display) = 0;
    virtual void updateDisplayBlendMode(BlendMode blendMode) = 0;
    virtual void updateDisplayVisible(bool visible) = 0;
    virtual void updateDisplayTransform() = 0;
	virtual void arriveAtFrame(Frame *frame, const SlotTimelineState *timelineState, AnimationState *animationState, bool isCross);
 //   virtual void calculateRelativeParentTransform() override;
	//virtual void updateGlobal(Transform &transform, Matrix &matrix) override;
private:
    DRAGON_BONES_DISALLOW_COPY_AND_ASSIGN(Slot);
};
NAME_SPACE_DRAGON_BONES_END
#endif  // CORE_SLOT_H
