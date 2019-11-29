#pragma once
#include "MathUtility.h"

namespace rumia
{
	namespace math
	{
		struct Vector3;
		struct alignas(16) Vector4
		{
		public:
			Vector4(float xx, float yy, float zz, float ww = 1.0f);
			Vector4(const Vector3& vec, float ww = 1.0f);
			Vector4();

			float Dot(const Vector4& rhs) const;
			float Dot3D(const Vector4& rhs) const;
			float Length() const;
			float Length3D() const;
			Vector4 Cross3D(const Vector4& rhs) const;

			void Normalize();
			Vector4 Normalized() const;

			void Scale(float scalar);
			Vector4 Scale(float scalar) const;

			/* Element wise operators **/
			Vector4 operator+(const Vector4& rhs) const;
			Vector4& operator+=(const Vector4& rhs);

			Vector4 operator-(const Vector4& rhs) const;
			Vector4& operator-=(const Vector4& rhs);

			Vector4 operator*(const Vector4& rhs) const;
			Vector4& operator*=(const Vector4& rhs);

			Vector4 operator/(const Vector4& rhs) const;
			Vector4& operator/=(const Vector4& rhs);

			Vector4 operator*(float val) const;
			Vector4& operator*=(float val);

			Vector4 operator/(float val) const;
			Vector4& operator/=(float val);

		public:
			union  
			{
				VectorRegister elements;
				struct
				{
					float x;
					float y;
					float z;
					float w;
				};
			};

		};
	}
}
