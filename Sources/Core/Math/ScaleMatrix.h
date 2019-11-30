#pragma once
#include "Matrix4x4.h"
#include "Vector3.h"

namespace rumia
{
	namespace math
	{
		class ScaleMatrix : public Matrix4x4
		{
		public:
			ScaleMatrix(const Vector3& scale);

		};

		FORCEINLINE ScaleMatrix::ScaleMatrix(const Vector3& scale) :
			Matrix4x4(
				scale.x, 0.0f, 0.0f, 0.0f,
				0.0f, scale.y, 0.0f, 0.0f,
				0.0f, 0.0f, scale.z, 0.0f,
				0.0f, 0.0f, 0.0f, 1.0f )
		{
		}
	}
}