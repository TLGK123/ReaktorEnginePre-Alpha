
#pragma once

//= INCLUDES ==================
#include "../EngineDefs.h"
#include <string>
//=============================

namespace TmingEngine
{
	class Vector3;
	class Matrix;

	class ENGINE_CLASS Vector4
	{
	public:
		Vector4()
		{
			x = 0;
			y = 0;
			z = 0;
			w = 0;
		}

		Vector4(float x, float y, float z, float w)
		{
			this->x = x;
			this->y = y;
			this->z = z;
			this->w = w;
		}

		Vector4(float value)
		{
			this->x = value;
			this->y = value;
			this->z = value;
			this->w = value;
		}

		Vector4(const Vector3& value, float w);
		Vector4(const Vector3& value);

		~Vector4(){}

		//= COMPARISON ================================================
		bool operator==(const Vector4& rhs) const
		{
			return x == rhs.x && y == rhs.y && z == rhs.z && w == rhs.w;
		}

		bool operator!=(const Vector4& rhs) const
		{
			return !(*this == rhs);
		}
		//=============================================================

		static Vector4 Transform(const Vector3& lhs, const Matrix& rhs);

		std::string ToString() const;

		float x, y, z, w;

		const float* Data() const { return &x; }

		static const Vector4 One;
		static const Vector4 Zero;
	};
}