#ifndef ANIMATION_TIMELINE_STATE_H
#define ANIMATION_TIMELINE_STATE_H

#include "../DragonBones.h"
#include "../geoms/ColorTransform.h"
#include "../geoms/Point.h"
#include "../geoms/Transform.h"

NAME_SPACE_DRAGON_BONES_BEGIN

class AnimationData;
class CurveData;
class TransformTimeline;
class Bone;
class AnimationState;

class TimelineState
{
    friend class AnimationState;
    friend class Bone;
    
	enum class UpdateState {UPDATE, UPDATE_ONCE, UNUPDATE};

public:
    std::string name;
    
private:
    bool _blendEnabled;
    bool _isComplete;
    bool _tweenTransform;
    bool _tweenScale;
    int _currentTime;
    int _currentFrameIndex;
    int _currentFramePosition;
    int _currentFrameDuration;
	int _lastTime;
    int _totalTime;
    float _weight;
    float _tweenEasing;
    
    UpdateState _updateState;
    Transform _transform;
    Transform _durationTransform;
    Transform _originTransform;
    Point _pivot;
    Point _durationPivot;
    Point _originPivot;
    
    Bone *_bone;
    AnimationState *_animationState;
    TransformTimeline *_timelineData;
	CurveData *_tweenCurve;
    
public:
    TimelineState();
    virtual ~TimelineState();
    
private:
	static std::vector<TimelineState*> _pool;
	static TimelineState* borrowObject();
	static void returnObject(TimelineState *timelineState);
	static void clearObjects();
    
	void fadeIn(Bone *bone, AnimationState *animationState, TransformTimeline *timeline);
    void fadeOut();
    void update(float progress);
    void updateMultipleFrame(float progress);
    void updateToNextFrame(int currentPlayTimes);
    void updateTween();
    void updateSingleFrame();
    void clear();
    
private:
    DRAGON_BONES_DISALLOW_COPY_AND_ASSIGN(TimelineState);
};
NAME_SPACE_DRAGON_BONES_END
#endif  // ANIMATION_TIMELINE_STATE_H
