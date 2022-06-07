#ifndef CB_MATH
#define CB_MATH

namespace CB
{

	static constexpr float fPI = 3.14159265358979323846f;
	static constexpr double dPI = 3.14159265358979323846;

	static constexpr float fTAU = 2 * fPI;
	static constexpr double dTAU = 2 * dPI;
	
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