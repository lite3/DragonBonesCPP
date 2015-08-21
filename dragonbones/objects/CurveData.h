#ifndef OBJECTS_CURVEDATA_H
#define OBJECTS_CURVEDATA_H

#include "../DragonBones.h"

NAME_SPACE_DRAGON_BONES_BEGIN
class CurveData
{
public:
	CurveData()
	{

	}
	virtual ~CurveData()
	{

	}

	float getValueByProgress(float progress)
	{
		// TODO
		return 0.f;
	}

	void refreshSampling()
	{

	}

	void bezierCurve(float t, Point outputPoint)
	{

	}

	bool isCurve()
	{
		// TODO
		return false;
	}
};

NAME_SPACE_DRAGON_BONES_END

#endif OBJECTS_CURVEDATA_H
