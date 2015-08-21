#ifndef ANIMATION_SLOTTIMELINESTATE_H
#define ANIMATION_SLOTTIMELINESTATE_H

#include "../DragonBones.h"
#include "../geoms/ColorTransform.h"

NAME_SPACE_DRAGON_BONES_BEGIN

class CurveData;
class Armature;
class SlotTimeline;
class Slot;
class Animation;
class AnimationState;
class Animation;
class Frame;
class SlotFrame;

class SlotTimelineState
{
	//friend class AnimationState;
	//friend class Slot;
	//friend class Animation;

	enum class UpdateState {UPDATE, UPDATE_ONCE, UNUPDATE};

public:
	std::string name;

private:
	float _weight;
	bool _blendEnabled;
	bool _isComplete;
	int _currentTime;
	int _currentFrameIndex;
	int _currentFramePosition;
	int _currentFrameDuration;
	int _totalTime;

	bool _tweenColor;
	float _tweenEasing;
	CurveData *_tweenCurve;

	float _rawAnimationScale;

	//UpdateState _updateState;
	int _updateMode;

	AnimationState *_animationState;
	Armature *_armature;
	Animation *_animation;
	Slot *_slot;
	SlotTimeline *_timelineData;
	ColorTransform _durationColor;

public:
	static std::vector<SlotTimelineState*> _pool;
	static SlotTimelineState* borrowObject();
	static void returnObject(SlotTimelineState *timelineState);
	static void clearObjects();

	SlotTimelineState();
	virtual ~SlotTimelineState();

	void fadeIn(Slot *slot, AnimationState *animationState, SlotTimeline *timelineData);

private:
	void update(float progress);
	void updateMultipleFrame(float progress);
	void updateToNextFrame(int currentPlayTimes);
	void updateTween();
	void updateSingleFrame();
	void clear();

private:
	DRAGON_BONES_DISALLOW_COPY_AND_ASSIGN(SlotTimelineState);
};

NAME_SPACE_DRAGON_BONES_END
#endif ANIMATION_SLOTTIMELINESTATE_H
