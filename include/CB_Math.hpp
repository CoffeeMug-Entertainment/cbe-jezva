#ifndef CB_MATH
#define CB_MATH

#include <cmath>

namespace CB
{

	static constexpr float fPI = acos(-1.0f);
	static constexpr double dPI = acos(-1.0);
	
	inline float deg2rad(const float deg)
	{
		return deg * fPI / 180.0f;
	}

	inline double deg2rad(const double deg)
	{
		return deg * dPI / 180.0;
	}

	inline int Sign(const int x)
	{
		return (x > 0) - (x < 0);
	}

	inline int Sign(const float x)
	{
		return (x > 0) - (x < 0);
	}

	inline int Sign(const double x)
	{
		return (x > 0) - (x < 0);
	}
}

#endif