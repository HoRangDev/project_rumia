#pragma once
#include "Vector4.h"
#include "MathUtility.h"

namespace rumia
{
	namespace math
	{
		struct alignas(16) Matrix4x4
		{
		public:
			Matrix4x4(
				float _m11 = 1.0f, float _m12 = 0.0f, float _m13 = 0.0f, float _m14 = 0.0f,
				float _m21 = 0.0f, float _m22 = 1.0f, float _m23 = 0.0f, float _m24 = 0.0f,
				float _m31 = 0.0f, float _m32 = 0.0f, float _m33 = 1.0f, float _m34 = 0.0f,
				float _m41 = 0.0f, float _m42 = 0.0f, float _m43 = 0.0f, float _m44 = 1.0f);

			Matrix4x4(float _elements[16]);

			Matrix4x4 operator*(const Matrix4x4& rhs) const;
			//Matrix4x4* operator*=(const Matrix4x4& rhs);

			void SetToZero();

			Matrix4x4 Transposed() const;

		public:
			/* Row-major order 4 by 4 matrix **/
			union
			{
				float elements[4][4];
				__m128 rows[4];

				struct
				{
					float m11, m12, m13, m14;
					float m21, m22, m23, m24;
					float m31, m32, m33, m34;
					float m41, m42, m43, m44;
				};
			};
		};

		static inline __m128 LinComb_SSE(const __m128& a, const Matrix4x4& mat)
		{
			__m128 result;
			result = _mm_mul_ps(
				_mm_shuffle_ps(a, a, _MM_SHUFFLE(0, 0, 0, 0)),
				mat.rows[0]);
			result = _mm_add_ps(
				result,
				_mm_mul_ps(
					_mm_shuffle_ps(a, a, _MM_SHUFFLE(1, 1, 1, 1)),
					mat.rows[1]));
			result = _mm_add_ps(
				result,
				_mm_mul_ps(
					_mm_shuffle_ps(a, a, _MM_SHUFFLE(2, 2, 2, 2)),
					mat.rows[2]));
			result = _mm_add_ps(
				result,
				_mm_mul_ps(
					_mm_shuffle_ps(a, a, _MM_SHUFFLE(3, 3, 3, 3)),
					mat.rows[3]));

			return result;
		}
	}
}
