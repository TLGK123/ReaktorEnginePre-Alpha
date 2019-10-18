
#pragma once

//= INCLUDES ==================
#include <cmath>
#include <math.h>
#include <limits>
#include "../EngineDefs.h"
//=============================

namespace TmingEngine
{
	enum Intersection
	{
		Outside,
		Inside,
		Intersects
	};

	static const float M_EPSILON = 0.000001f;
	static const float PI = 3.14159265358979323846264338327950288f;
	static const float PI_2 = 6.283185307f;
	static const float PI_DIV_2 = 1.570796327f;
	static const float PI_DIV_4 = 0.785398163f;
	static const float PI_INV = 0.318309886f;
	static const float DEG_TO_RAD = PI / 180.0f;
	static const float DEG_TO_RAD_2 = PI / 360.0f;
	static const float RAD_TO_DEG = 180.0f / PI;

	inline ENGINE_CLASS double Cot(float x) { return cos(x) / sin(x); }
	inline ENGINE_CLASS float CotF(float x) { return cosf(x) / sinf(x); }
	inline ENGINE_CLASS float DegreesToRadians(float degrees) { return degrees * DEG_TO_RAD; }
	inline ENGINE_CLASS float RadiansToDegrees(float radians) { return radians * RAD_TO_DEG; }

	template <typename T>
	T Clamp(T x, T a, T b) { return x < a ? a : (x > b ? b : x); }

	// Lerp linearly between to values
	template <class T, class U>
	T Lerp(T lhs, T rhs, U t) { return lhs * ((U)1.0 - t) + rhs * t; }

	// Returns the absolute value
	template <class T>
	T Abs(T value) { return value >= 0.0 ? value : -value; }

	// Check for equality but allow for a small error
	template <class T>
	bool Equals(T lhs, T rhs) { return lhs + std::numeric_limits<T>::epsilon() >= rhs && lhs - std::numeric_limits<T>::epsilon() <= rhs; }

	template <class T>
	T Max(T a, T b) { return a > b ? a : b; }

	template <class T>
	T Min(T a, T b) { return a < b ? a : b; }

	template <class T>
	T Sqrt(T x) { return sqrt(x); }

	template <class T>
	T Floor(T x) { return floor(x); }

	template <class T>
	T Ceil(T x) { return ceil(x); }

	template <class T>
	T Round(T x) { return round(x); }
}