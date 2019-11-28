#pragma once

namespace rumia
{
	namespace math
	{
		struct Vector2
		{
		public:
			Vector2(float xx, float yy);
			Vector2();

			float Dot(const Vector2& rhs) const;
			float Length() const;

			void Normalize();
			Vector2 Normalized() const;

			/* Element wise operators **/
			Vector2 operator+(const Vector2& rhs) const;
			Vector2& operator+=(const Vector2& rhs);

			Vector2 operator-(const Vector2& rhs) const;
			Vector2& operator-=(const Vector2& rhs);

			Vector2 operator*(const Vector2& rhs) const;
			Vector2& operator*=(const Vector2& rhs);

			Vector2 operator/(const Vector2& rhs) const;
			Vector2& operator/=(const Vector2& rhs);

			Vector2 operator*(float val) const;
			Vector2& operator*=(float val);

			Vector2 operator/(float val) const;
			Vector2& operator/=(float val);

		public:
			float x;
			float y;

		};
	}
}