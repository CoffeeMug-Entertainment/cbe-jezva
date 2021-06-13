#ifndef CB_MATH
#define CB_MATH value

namespace CB
{

	inline int Sign(int x)
	{
		return (x > 0) - (x < 0);
	}

	inline int Sign(float x)
	{
		return (x > 0) - (x < 0);
	}

	inline int Sign(double x)
	{
		return (x > 0) - (x < 0);
	}
}



#endif