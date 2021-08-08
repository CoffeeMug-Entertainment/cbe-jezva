#ifndef CB_VEC2
#define CB_VEC2

#include <cmath>

namespace CB
{
	struct Vec2
	{
		float x;
		float y;

		// Additional vector info

		float magnitude() const
		{
			return std::sqrt((x * x) + (y * y));
		}

		Vec2 unit() const
		{
			return {(this->x > 0.0f) - (this->x < 0.0f), (this->y > 0.0f) - (this->y < 0.0f)};
			//CB_Math.hpp way, essentially the same thing:
			//return {CB::Sign(this->x), CB::Sign(this->y)};
		}

		//Operations

		Vec2 normalized() const
		{
			float r = 1 / magnitude();
			return {this->x * r, this->y * r};
		}

		float dot (const Vec2& second)
		{
			return this->x * second.x + this->y * second.y;
		}

		float cross (const Vec2& second)
		{
			return this->x * second.y - this->y * second.x;
		}

		Vec2 perpendicular() const
		{
			return {-y, x};
		}

		Vec2 rotated(const float angle) const
		{
			return {this->x * cos(angle) - this->y * sin(angle), this->x * sin(angle) + this->y * cos(angle)};
		}

		//Overloads

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

		//Useful pre-definitions
		static const Vec2 ZERO;
		static const Vec2 ONE;
		static const Vec2 UP;
		static const Vec2 DOWN;
		static const Vec2 LEFT;
		static const Vec2 RIGHT;
	};

	inline constexpr Vec2 Vec2::ZERO {0, 0};
	inline constexpr Vec2 Vec2::ONE {1, 1};
	inline constexpr Vec2 Vec2::UP {0, -1};
	inline constexpr Vec2 Vec2::DOWN {0,  1};
	inline constexpr Vec2 Vec2::LEFT {-1, 0};
	inline constexpr Vec2 Vec2::RIGHT {1, 0};
}
#endif
