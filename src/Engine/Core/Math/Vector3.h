/*
			This file is part of:
				TmingEngine
			https://github.com/xiaomingfun/TmingEngine

   Copyright 2018 - 2020 TmingEngine

   File creator: littleblue

   TmingEngine is open-source software and you can redistribute it and/or modify
   it under the terms of the License; besides, anyone who use this file/software must include this copyright announcement.

   Licensed under the Apache License, Version 2.0 (the "License");
   you may not use this file except in compliance with the License.
   You may obtain a copy of the License at

	   http://www.apache.org/licenses/LICENSE-2.0

   Unless required by applicable law or agreed to in writing, software
   distributed under the License is distributed on an "AS IS" BASIS,
   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
   See the License for the specific language governing permissions and
   limitations under the License.
*/

#ifndef TmingEngine_Engine_Math_Vector3_h_
#define TmingEngine_Engine_Math_Vector3_h_

#include <stdio.h>
#include <math.h>
#include <string>
#include <sstream>
#include <iostream>
#include <iomanip>

#include "Core/EngineDefs.h"
#include "glm/glm.hpp"

using namespace glm;
using namespace std;

namespace TmingEngine
{
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

		Vector3(vec3 v)
		{
			this->x = v.x;
			this->y = v.y;
			this->z = v.z;
		}

		bool operator ==(const Vector3& other) const
		{
			return x == other.x && y == other.y && z == other.z;
		}

		Vector3 operator +(const Vector3& other) const
		{
			return Vector3(x + other.x, y + other.y, z + other.z);
		}

		Vector3 operator +(int  offset) const
		{
			return Vector3(x + offset, y + offset, z + offset);
		}

		Vector3 operator -(const Vector3& other) const
		{
			return Vector3(x - other.x, y - other.y, z - other.z);
		}

		Vector3 operator -(float other) const
		{
			return Vector3(x - other, y - other, z - other);
		}

		Vector3 operator +(float other) const
		{
			return Vector3(x + other, y + other, z + other);
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
			float v1 = (x / len);
			float v2 = (y / len);
			float v3 = (z / len);

			return Vector3(v1, v2, v3);
		}

		Vector3 operator * (const float other)const
		{
			return Vector3(x * other, y * other, z * other);
		}

		friend ostream& operator<<(ostream& stream, const Vector3 c)
		{
			ostringstream oss;
			oss << setiosflags(ios::fixed | ios::right) << setw(8) << setprecision(2) << "(" << c.x << " , " << c.y << " , " << c.z << ")" << endl;

			std::string s = "";
			s = string(oss.str());
			stream << s;
			return stream;
		}
	};
}

#endif //TmingEngine_Engine_Math_Vector3_h_