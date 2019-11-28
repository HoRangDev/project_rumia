#include "Vector2.h"
#include <cmath>

namespace rumia
{
	namespace math
	{
		Vector2::Vector2(float xx, float yy) :
			x(xx),
			y(yy)
		{
		}

		Vector2::Vector2() :
			Vector2(0.0f, 0.0f)
		{
		}

		float Vector2::Dot(const Vector2& target) const
		{
			return (x * target.x + y * target.y);
		}

		float Vector2::Length() const
		{
			return std::sqrtf(x * x + y * y);
		}

		void Vector2::Normalize()
		{
			float len = Length();
			(*this) /= len;
		}

		Vector2 Vector2::Normalized() const
		{
			float len = Length();
			return ((*this) / len);
		}

		Vector2 Vector2::operator+(const Vector2 & rhs) const
		{
			return Vector2(x + rhs.x, y + rhs.y);
		}

		Vector2& Vector2::operator+=(const Vector2 & rhs)
		{
			this->x += rhs.x;
			this->y += rhs.y;
			return (*this);
		}

		Vector2 Vector2::operator-(const Vector2 & rhs) const
		{
			return Vector2(x - rhs.x, y - rhs.y);
		}

		Vector2& Vector2::operator-=(const Vector2 & rhs)
		{
			this->x -= rhs.x;
			this->y -= rhs.y;
			return (*this);
		}

		Vector2 Vector2::operator*(const Vector2 & rhs) const
		{
			return Vector2(x * rhs.x, y * rhs.y);
		}

		Vector2& Vector2::operator*=(const Vector2 & rhs)
		{
			this->x *= rhs.x;
			this->y *= rhs.y;
			return (*this);
		}

		Vector2 Vector2::operator/(const Vector2 & rhs) const
		{
			return Vector2(x / rhs.x, y / rhs.y);
		}

		Vector2& Vector2::operator/=(const Vector2 & rhs)
		{
			this->x /= rhs.x;
			this->y /= rhs.y;
			return (*this);
		}

		Vector2 Vector2::operator*(float val) const
		{
			return Vector2(x * val, y * val);
		}

		Vector2& Vector2::operator*=(float val)
		{
			this->x *= val;
			this->y *= val;
			return (*this);
		}

		Vector2 Vector2::operator/(float val) const
		{
			float inv = 1.0f / val;
			return Vector2(x * inv, y * inv);
		}

		Vector2& Vector2::operator/=(float val)
		{
			float inv = 1.0f / val;
			this->x *= inv;
			this->y *= inv;
			return (*this);
		}
	}
}