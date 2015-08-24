#ifndef OBJECTS_CURVEDATA_H
#define OBJECTS_CURVEDATA_H

#include "../DragonBones.h"
#include "../geoms/Point.h"

NAME_SPACE_DRAGON_BONES_BEGIN
class CurveData
{
	//static int SamplingTimes = 20;
	//static float SamplingStep = 0.05f;
	
private:
	bool _dataChanged;
	std::vector<Point*> _pointList;
	std::vector<Point*> sampling;

public:
	CurveData()
	{

	}
	virtual ~CurveData()
	{

	}

	float getValueByProgress(float progress)
	{
		//if(_dataChanged)
		//{
		//	refreshSampling();
		//}
		//for (int i = 0; i < SamplingTimes-1; i++) 
		//{
		//	Point *point= sampling[i];
		//	if (point->x >= progress) 
		//	{
		//		if(i == 0)
		//		{
		//			return point->y * progress / point->x;
		//		}
		//		else
		//		{
		//			Point *prevPoint = sampling[i-1];
		//			return prevPoint->y + (point->y - prevPoint->y) * (progress - prevPoint->x) / (point->x - prevPoint->x);
		//		}
		//	}
		//}
		//return point->y + (1 - point.y) * (progress - point.x) / (1 - point.x);
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
