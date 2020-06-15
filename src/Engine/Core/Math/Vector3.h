//The MIT License
//
//Copyright(c) 2018 - 2019 littleblue
//
//Permission is hereby granted, free of charge, to any person obtaining a copy
//of this softwareand associated documentation files(the "Software"), to deal
//in the Software without restriction, including without limitation the rights
//to use, copy, modify, merge, publish, distribute, sublicense, and / or sell
//copies of the Software, and to permit persons to whom the Software is furnished
//to do so, subject to the following conditions :
//
//The above copyright noticeand this permission notice shall be included in
//all copies or substantial portions of the Software.
//
//THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
//IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS
//FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.IN NO EVENT SHALL THE AUTHORS OR
//COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER
//IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
//CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

#pragma once
#include "../EngineDefs.h"
#include <string>
#include <math.h>
#include "im.h"

namespace TmingEngine {
	ENGINE_CLASS class Vector3
	{
	public:
		float x = 0;
		float y = 0;
		float z = 0;

		Vector3()
		{
		}

		Vector3(float x, float y, float z)
		{
			this->x = x;
			this->y = y;
			this->z = z;
		}

		Vector3(glm::vec3 v)
		{
			this->x = v.x;
			this->y = v.y;
			this->z = v.z;
		}

		std::string ToString() const;

		bool operator ==(const Vector3& other) const
		{
			return x == other.x && y == other.y && z == other.z;
		}

		Vector3 operator +(const Vector3& other) const
		{
			return Vector3(x + other.x, y + other.y, z + other.z);
		}

		Vector3 operator -(const Vector3& other) const
		{
			return Vector3(x - other.x, y - other.y, z - other.z);
		}

		Vector3 Cross(const Vector3& v2) const
		{
			float x_ = y * v2.z - v2.y * z;
			float y_ = v2.x * z - x * v2.z;
			float z_ = x * v2.y - y * v2.x;
			return Vector3(x_, y_, z_);
		}

		float Dot(const Vector3& v2)
		{
			return x * v2.x + y * v2.y + z * v2.z;
		}

		Vector3 Normalize() const
		{
			float len = sqrt(x * x + y * y + z * z);
			float v1 = abs(x / len);
			float v2 = abs(y / len);
			float v3 = abs(z / len);

			return Vector3(v1, v2, v3);
		}

		Vector3 operator * (const float other)const
		{
			return Vector3(x * other, y * other, z * other);
		}
	};
}
