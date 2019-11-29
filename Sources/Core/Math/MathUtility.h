#pragma once
#include "Macros.h"
#include <tuple>
#include <emmintrin.h>

constexpr float PI = (3.1415926535897932f);
constexpr float INV_PI = (1.0f / PI);
constexpr float HALF_PI = (PI / 2.0f);

static FORCEINLINE float DegreesToRadians(float degrees)
{
	return (degrees * (PI / 180.0f));
}

static FORCEINLINE float RadiansToDegrees(float radians)
{
	return (radians * (180.0f / PI));
}

/**
* 주어진 radians 값에 대한 sin, cos값을 minimax approximation 을 이용하여 계산.
*
* @param	radians	입력 각도(라디안값)
* @return	first	계산된 sin 값	
* @return	second	계산된 cos 값
*/
static FORCEINLINE std::pair<float, float> SinCos(float radians)
{
	float quotient = (INV_PI * 0.5f) * radians; // (rad/2pi)
	if (radians >= 0.0f)
	{
		quotient = (float)((int)(quotient + 0.5f));
	}
	else
	{
		quotient = (float)((int)(quotient - 0.5f));
	}

	// radians => [-pi, pi]
	float y = radians - (2.0f * PI) * quotient;

	// y => [-pi/2, pi/2]
	float sign = 0.0f;
	if (y > HALF_PI)
	{
		y = PI - y;
		sign = -1.0f;
	}
	else if (y < -HALF_PI)
	{
		y = -PI - y;
		sign = -1.0f;
	}
	else
	{
		sign = 1.0f;
	}

	float y2 = y * y;
	return {
		(((((-2.3889859e-08f * y2 + 2.7525562e-06f) * y2 - 0.00019840874f) * y2 + 0.0083333310f) * y2 - 0.16666667f) * y2 + 1.0f) * y,
		sign * (((((-2.6051615e-07f * y2 + 2.4760495e-05f) * y2 - 0.0013888378f) * y2 + 0.041666638f) * y2 - 0.5f) * y2 + 1.0f) };
}

using VectorRegister = __m128;
using VectorRegisterInt = __m128i;
using VectorRegisterDouble = __m128d;

#define SHUFFLEMASK(A0, A1, B2, B3) ( (A0) | (A1 << 2) | (B2 << 4) | (B3 << 6) )

FORCEINLINE VectorRegister VectorAdd(const VectorRegister& v1, const VectorRegister& v2)
{
	return _mm_add_ps(v1, v2);
}

FORCEINLINE VectorRegister VectorMultiply(const VectorRegister& v1, const VectorRegister& v2)
{
	return _mm_mul_ps(v1, v2);
}

FORCEINLINE VectorRegister VectorSubtract(const VectorRegister& v1, const VectorRegister& v2)
{
	return _mm_sub_ps(v1, v2);
}