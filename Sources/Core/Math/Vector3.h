#pragma once

namespace rumia
{
	namespace math
	{
		struct Vector2;
		struct Vector3
		{
		public:
			Vector3(float xx, float yy, float zz);
			Vector3(const Vector2& vec, float scalar);
			Vector3();

			float Dot(const Vector3& rhs) const;
			float Length() const;
			Vector3 Cross(const Vector3& rhs) const;

			void Normalize();
			Vector3 Normalized() const;

			/* Element wise operators **/
			Vector3 operator+(const Vector3& rhs) const;
			Vector3& operator+=(const Vector3& rhs);

			Vector3 operator-(const Vector3& rhs) const;
			Vector3& operator-=(const Vector3& rhs);

			Vector3 operator*(const Vector3& rhs) const;
			Vector3& operator*=(const Vector3& rhs);

			Vector3 operator/(const Vector3& rhs) const;
			Vector3& operator/=(const Vector3& rhs);

			Vector3 operator*(float val) const;
			Vector3& operator*=(float val);

			Vector3 operator/(float val) const;
			Vector3& operator/=(float val);

		public:
			float x;
			float y;
			float z;

		};
	}
}