#include "Matrix4x4.h"
#include <iostream>

namespace rumia
{
	namespace math
	{
		Matrix4x4::Matrix4x4(
			float _m11 /* = 1.0f */, float _m12 /* = 0.0f */, float _m13 /* = 0.0f */, float _m14 /* = 0.0f */,
			float _m21 /* = 0.0f */, float _m22 /* = 1.0f */, float _m23 /* = 0.0f */, float _m24 /* = 0.0f */,
			float _m31 /* = 0.0f */, float _m32 /* = 0.0f */, float _m33 /* = 1.0f */, float _m34 /* = 0.0f */,
			float _m41 /* = 0.0f */, float _m42 /* = 0.0f */, float _m43 /* = 0.0f */, float _m44 /* = 1.0f */) :
			m11(_m11), m12(_m12), m13(_m13), m14(_m14),
			m21(_m21), m22(_m22), m23(_m23), m24(_m24),
			m31(_m31), m32(_m32), m33(_m33), m34(_m34),
			m41(_m41), m42(_m42), m43(_m43), m44(_m44)
		{
		}

		Matrix4x4::Matrix4x4(float _elements[16]) :
			Matrix4x4(
				_elements[0], _elements[1], _elements[2], _elements[3],
				_elements[4], _elements[5], _elements[6], _elements[7],
				_elements[8], _elements[9], _elements[10], _elements[11],
				_elements[12], _elements[13], _elements[14], _elements[15])
		{
		}

		Matrix4x4 Matrix4x4::operator*(const Matrix4x4& rhs) const
		{
			// dot(lhs.row, rhs.col)
			//return Matrix4x4(
			//	m11 * rhs.m11 + m12 * rhs.m21 + m13 * rhs.m31 + m14 * rhs.m41,
			//	m11 * rhs.m12 + m12 * rhs.m22 + m13 * rhs.m32 + m14 * rhs.m42,
			//	m11 * rhs.m13 + m12 * rhs.m23 + m13 * rhs.m33 + m14 * rhs.m43,
			//	m11 * rhs.m14 + m12 * rhs.m24 + m13 * rhs.m34 + m14 * rhs.m44,


			//	m21 * rhs.m11 + m22 * rhs.m21 + m23 * rhs.m31 + m24 * rhs.m41,
			//	m21 * rhs.m12 + m22 * rhs.m22 + m23 * rhs.m32 + m24 * rhs.m42,
			//	m21 * rhs.m13 + m22 * rhs.m23 + m23 * rhs.m33 + m24 * rhs.m43,
			//	m21 * rhs.m14 + m22 * rhs.m24 + m23 * rhs.m34 + m24 * rhs.m44,


			//	m31 * rhs.m11 + m32 * rhs.m21 + m33 * rhs.m31 + m34 * rhs.m41,
			//	m31 * rhs.m12 + m32 * rhs.m22 + m33 * rhs.m32 + m34 * rhs.m42,
			//	m31 * rhs.m13 + m32 * rhs.m23 + m33 * rhs.m33 + m34 * rhs.m43,
			//	m31 * rhs.m14 + m32 * rhs.m24 + m33 * rhs.m34 + m34 * rhs.m44,


			//	m41 * rhs.m11 + m42 * rhs.m21 + m43 * rhs.m31 + m44 * rhs.m41,
			//	m41 * rhs.m12 + m42 * rhs.m22 + m43 * rhs.m32 + m44 * rhs.m42,
			//	m41 * rhs.m13 + m42 * rhs.m23 + m43 * rhs.m33 + m44 * rhs.m43,
			//	m41 * rhs.m14 + m42 * rhs.m24 + m43 * rhs.m34 + m44 * rhs.m44);
			Matrix4x4 result;
			Matrix4x4 transposed_rhs = rhs.Transposed();

			result.rows[0] = LinComb_SSE(this->rows[0], transposed_rhs);
			result.rows[1] = LinComb_SSE(this->rows[1], transposed_rhs);
			result.rows[2] = LinComb_SSE(this->rows[2], transposed_rhs);
			result.rows[3] = LinComb_SSE(this->rows[3], transposed_rhs);

			return result;
		}

		void Matrix4x4::SetToZero()
		{
			std::memset(this->elements, 0, sizeof(float) * 16);
		}

		Matrix4x4 Matrix4x4::Transposed() const
		{
			Matrix4x4 result;

			VectorRegister tmp[4];
			tmp[0] = _mm_shuffle_ps(rows[0], rows[1], SHUFFLEMASK(0, 1, 0, 1));
			tmp[2] = _mm_shuffle_ps(rows[0], rows[1], SHUFFLEMASK(2, 3, 2, 3));
			tmp[1] = _mm_shuffle_ps(rows[2], rows[3], SHUFFLEMASK(0, 1, 0, 1));
			tmp[3] = _mm_shuffle_ps(rows[2], rows[3], SHUFFLEMASK(2, 3, 2, 3));

			result.rows[0] = _mm_shuffle_ps(tmp[0], tmp[1], SHUFFLEMASK(0, 2, 0, 2));
			result.rows[1] = _mm_shuffle_ps(tmp[0], tmp[1], SHUFFLEMASK(1, 3, 1, 3));
			result.rows[2] = _mm_shuffle_ps(tmp[2], tmp[3], SHUFFLEMASK(0, 2, 0, 2));
			result.rows[3] = _mm_shuffle_ps(tmp[2], tmp[3], SHUFFLEMASK(1, 3, 1, 3));

			return result;
		}
	}
}