#ifndef CBE_VEC2
#define CBE_VEC2

#include <cmath>

namespace CB
{
	struct Vec2
	{
		float x;
		float y;

		// Prefix
		Vec2 operator-()
		{
			return {-this->x, -this->y};
		}

		// Vector operations
		Vec2 operator+(const Vec2& second)
		{
			return {this->x + second.x, this->y + second.y};
		}

		Vec2 operator-(const Vec2& second)
		{
			return {this->x - second.x, this->y - second.y};
		}

		Vec2 operator*(const Vec2& second)
		{
			return {this->x* second.x, this->y * second.y};
		}

		Vec2 operator/(const Vec2& second)
		{
			return {this->x / second.x, this->y / second.y};
		}

		Vec2& operator+=(const Vec2& second)
		{
			this->x += second.x;
			this->y += second.y;
			return *this;
		}

		Vec2& operator-=(const Vec2& second)
		{
			this->x -= second.x;
			this->y -= second.y;
			return *this;
		}

		Vec2& operator*=(const Vec2& second)
		{
			this->x *= second.x;
			this->y *= second.y;
			return *this;
		}
		
		Vec2& operator/=(const Vec2& second)
		{
			this->x /= second.x;
			this->y /= second.y;
			return *this;
		}

		bool operator==(const Vec2& second)
		{
			return this->x == second.x &&
					this->y == second.y;
		}

		bool operator!=(const Vec2& second)
		{
			return !(*this == second);
		}

		//Scalar operations

		Vec2 operator*(const float& scalar)
		{
			return {this->x * scalar, this->y * scalar};
		}

		Vec2 operator/(const float& scalar)
		{
			return {this->x / scalar, this->y / scalar};
		}

		Vec2& operator*=(const float& scalar)
		{
			this->x *= scalar;
			this->y *= scalar;
			return *this;
		}

		Vec2& operator/=(const float& scalar)
		{
			this->x /= scalar;
			this->y /= scalar;
			return *this;
		}

		float magnitude() const
		{
			return std::sqrt((x * x) + (y * y));
		}

		//TODO fhomolka 04/06/2021 14:33 -> Create these instances
		static const Vec2 Zero;
		static const Vec2 One;
		static const Vec2 Up;
		static const Vec2 Down;
		static const Vec2 Left;
		static const Vec2 Right;
	};

	//TODO fhomolka 04/06/2021 14:33 ->Put this in a CPP
	//const Vec2 Vec2::Zero = {0,0};

}



#endif