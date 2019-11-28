#include "Vector4.h"
#include "Vector3.h"
#include <cmath>

namespace rumia
{
	namespace math
	{
		Vector4::Vector4(float xx, float yy, float zz, float ww) :
			x(xx),
			y(yy),
			z(zz),
			w(ww)
		{
		}

		Vector4::Vector4(const Vector3& vec, float ww) :
			Vector4(vec.x, vec.y, vec.z, ww)
		{
		}

		Vector4::Vector4() :
			Vector4(0.0f, 0.0f, 0.0f, 0.0f)
		{
		}

		float Vector4::Dot(const Vector4& target) const
		{
			return (
				x * target.x +
				y * target.y +
				z * target.z +
				w * target.w);
		}

		float Vector4::Dot3D(const Vector4 & target) const
		{
			return (
				x * target.x +
				y * target.y +
				z * target.z);
		}

		float Vector4::Length() const
		{
			return std::sqrtf(x * x + y * y + z * z + w * w);
		}

		float Vector4::Length3D() const
		{
			return std::sqrtf(x * x + y * y + z * z);
		}

		Vector4 Vector4::Cross3D(const Vector4 & rhs) const
		{
			return Vector4(
				y * rhs.z + z * rhs.y,
				z * rhs.x + x * rhs.z,
				x * rhs.y + y * rhs.x);
		}

		void Vector4::Normalize()
		{
			float len = Length();
			(*this) /= len;
		}

		Vector4 Vector4::Normalized() const
		{
			float len = Length();
			return ((*this) / len);
		}

		void Vector4::Scale(float scalar)
		{
			this->x *= scalar;
			this->y *= scalar;
			this->z *= scalar;
		}

		Vector4 Vector4::Scale(float scalar) const
		{
			return Vector4(x * scalar, y * scalar, z * scalar, w);
		}

		Vector4 Vector4::operator+(const Vector4 & rhs) const
		{
			return Vector4(x + rhs.x, y + rhs.y, z + rhs.z, w + rhs.w);
		}

		Vector4& Vector4::operator+=(const Vector4 & rhs)
		{
			this->x += rhs.x;
			this->y += rhs.y;
			this->z += rhs.z;
			this->w += rhs.w;
			return (*this);
		}

		Vector4 Vector4::operator-(const Vector4 & rhs) const
		{
			return Vector4(x - rhs.x, y - rhs.y, z - rhs.z, w - rhs.w);
		}

		Vector4& Vector4::operator-=(const Vector4 & rhs)
		{
			this->x -= rhs.x;
			this->y -= rhs.y;
			this->z -= rhs.z;
			this->w -= rhs.w;
			return (*this);
		}

		Vector4 Vector4::operator*(const Vector4 & rhs) const
		{
			return Vector4(x * rhs.x, y * rhs.y, z * rhs.z, w * rhs.w);
		}

		Vector4& Vector4::operator*=(const Vector4 & rhs)
		{
			this->x *= rhs.x;
			this->y *= rhs.y;
			this->z *= rhs.z;
			this->w *= rhs.w;
			return (*this);
		}

		Vector4 Vector4::operator/(const Vector4 & rhs) const
		{
			return Vector4(x / rhs.x, y / rhs.y, z / rhs.z, w / rhs.w);
		}

		Vector4& Vector4::operator/=(const Vector4 & rhs)
		{
			this->x /= rhs.x;
			this->y /= rhs.y;
			this->z /= rhs.z;
			this->w /= rhs.w;
			return (*this);
		}

		Vector4 Vector4::operator*(float val) const
		{
			return Vector4(x * val, y * val, z * val, w * val);
		}

		Vector4& Vector4::operator*=(float val)
		{
			this->x *= val;
			this->y *= val;
			this->z *= val;
			this->w *= val;
			return (*this);
		}

		Vector4 Vector4::operator/(float val) const
		{
			float inv = 1.0f / val;
			return Vector4(x * inv, y * inv, z * inv, w * inv);
		}

		Vector4& Vector4::operator/=(float val)
		{
			float inv = 1.0f / val;
			this->x *= inv;
			this->y *= inv;
			this->z *= inv;
			this->w *= inv;
			return (*this);
		}
	}
}
