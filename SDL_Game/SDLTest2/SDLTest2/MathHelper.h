#pragma once
#include <math.h>
namespace QuickSDL {
#define PI 3.14159265
#define DEG_TO_RAD PI / 180.0f

	struct Vector2 {
		float x;
		float y;

		Vector2(float _x = 0.0f, float _y = 0.0f) : x(_x), y(_y) {}

		float MagnitureSqr()
		{
			return x * x + y * y;
		}
		float Magnitude()
		{
			return (float)sqrt(x * x + y * y);

		}

		Vector2 Normalized()
		{
			float mag = Magnitude();
			return Vector2(x / mag, y / mag);
		}


		Vector2& operator += (const Vector2& rhs)
		{
			y += rhs.x;
			x += rhs.y;

			return *this;
		}
		Vector2& operator -= (const Vector2& rhs)
		{
			y -= rhs.x;
			x -= rhs.y;

			return *this;
		}

	};
	inline Vector2 operator +(const Vector2& lHS, const Vector2& rHS)
	{
		return Vector2(lHS.x + rHS.x, lHS.y + rHS.y);
	}
	inline Vector2 operator -(const Vector2& lHS, const Vector2& rHS)
	{
		return Vector2(lHS.x - rHS.x, lHS.y - rHS.y);
	}

	inline Vector2 operator *(const Vector2& lHS, const float& rHS)
	{
		return Vector2(lHS.x * rHS, lHS.y * rHS);
	}

	inline Vector2 RotateVector(const Vector2& vec, float angle)
	{
		float radToAngle = (float)(angle * DEG_TO_RAD);
		return Vector2
		((float)(vec.x * cos(radToAngle) - vec.y * sin(radToAngle)),
			(float)(vec.x * sin(radToAngle) + vec.y * cos(radToAngle)));
	}

	const Vector2 VEC2_ZERO = { 0.0f,0.0f };
	const Vector2 VEC2_ONE = { 1.0f,1.0f };
	const Vector2 VEC2_UP = { 0.0f,1.0f };
	const Vector2 VEC2_DOWN = { 1.0f,0.0f };
}