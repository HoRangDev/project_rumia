#include "Vector3.h"
#include "Vector2.h"
#include <cmath>

namespace rumia
{
	namespace math
	{
		Vector3::Vector3(float xx, float yy, float zz) :
			x(xx),
			y(yy),
			z(zz)
		{
		}

		Vector3::Vector3(const Vector2& vec, float scalar) :
			Vector3(vec.x, vec.y, scalar)
		{
		}

		Vector3::Vector3() :
			Vector3(0.0f, 0.0f, 0.0f)
		{
		}

		float Vector3::Dot(const Vector3& target) const
		{
			return (
				x * target.x +
				y * target.y +
				z * target.z);
		}

		float Vector3::Length() const
		{
			return std::sqrtf(x * x + y * y + z * z);
		}

		Vector3 Vector3::Cross(const Vector3 & rhs) const
		{
			return Vector3(
				y * rhs.z + z * rhs.y,
				z * rhs.x + x * rhs.z,
				x * rhs.y + y * rhs.x);
		}

		void Vector3::Normalize()
		{
			float len = Length();
			(*this) /= len;
		}

		Vector3 Vector3::Normalized() const
		{
			float len = Length();
			return ((*this) / len);
		}

		Vector3 Vector3::operator+(const Vector3 & rhs) const
		{
			return Vector3(x + rhs.x, y + rhs.y, z + rhs.z);
		}

		Vector3& Vector3::operator+=(const Vector3 & rhs)
		{
			this->x += rhs.x;
			this->y += rhs.y;
			this->z += rhs.z;
			return (*this);
		}

		Vector3 Vector3::operator-(const Vector3 & rhs) const
		{
			return Vector3(x - rhs.x, y - rhs.y, z - rhs.z);
		}

		Vector3& Vector3::operator-=(const Vector3 & rhs)
		{
			this->x -= rhs.x;
			this->y -= rhs.y;
			this->z -= rhs.z;
			return (*this);
		}

		Vector3 Vector3::operator*(const Vector3 & rhs) const
		{
			return Vector3(x * rhs.x, y * rhs.y, z * rhs.z);
		}

		Vector3& Vector3::operator*=(const Vector3 & rhs)
		{
			this->x *= rhs.x;
			this->y *= rhs.y;
			this->z *= rhs.z;
			return (*this);
		}

		Vector3 Vector3::operator/(const Vector3 & rhs) const
		{
			return Vector3(x / rhs.x, y / rhs.y, z / rhs.z);
		}

		Vector3& Vector3::operator/=(const Vector3 & rhs)
		{
			this->x /= rhs.x;
			this->y /= rhs.y;
			this->z /= rhs.z;
			return (*this);
		}

		Vector3 Vector3::operator*(float val) const
		{
			return Vector3(x * val, y * val, z * val);
		}

		Vector3& Vector3::operator*=(float val)
		{
			this->x *= val;
			this->y *= val;
			this->z *= val;
			return (*this);
		}

		Vector3 Vector3::operator/(float val) const
		{
			float inv = 1.0f / val;
			return Vector3(x * inv, y * inv, z * inv);
		}

		Vector3& Vector3::operator/=(float val)
		{
			float inv = 1.0f / val;
			this->x *= inv;
			this->y *= inv;
			this->z *= inv;
			return (*this);
		}
	}
}