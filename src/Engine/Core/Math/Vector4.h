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

#ifndef TmingEngine_Engine_Math_Vector4_h_
#define TmingEngine_Engine_Math_Vector4_h_

#include <stdio.h>
#include <math.h>
#include <string>
#include <sstream>
#include <iostream>
#include <iomanip>

#include "Core/EngineDefs.h"
#include "Core/Math/MathFunctions.hpp"

namespace TmingEngine
{
	ENGINE_CLASS class Vector4
	{
	public:
		float x = 0;
		float y = 0;
		float z = 0;
		float w = 0;
		Vector4()
		{
		}

		Vector4(float x, float y, float z, float w)
		{
			this->x = x;
			this->y = y;
			this->z = z;
			this->w = w;
		}



		bool operator ==(const Vector4& other) const
		{
			return x == other.x && y == other.y && z == other.z && w == other.w;
		}

		Vector4 operator +(const Vector4& other) const
		{
			return Vector4(x + other.x, y + other.y, z + other.z,w+ other.w);
		}

		Vector4 operator -(const Vector4& other) const
		{
			return Vector4(x - other.x, y - other.y, z - other.z, w - other.w);
		}


		Vector4 operator +(float  offset) const
		{
			return Vector4(x + offset, y + offset, z + offset, w + offset);
		}

		Vector4 operator -(float  offset) const
		{
			return Vector4(x - offset, y - offset, z - offset, w - offset);
		}


		Vector4 operator *(float  offset) const
		{
			return Vector4(x * offset, y * offset, z * offset, w * offset);
		}

		Vector4 operator /(float  offset) const
		{
			return Vector4(x / offset, y / offset, z / offset, w / offset);
		}

		operator Vector3()
		{
			return Vector3(x, y, z);
		}

		friend std::ostream& operator<<(std::ostream& stream, const Vector4 c)
		{
			std::ostringstream oss;
			oss << std::setiosflags(std::ios::fixed | std::ios::right) << std::setw(8) << std::setprecision(2) << "(" << c.x << " , " << c.y << " , " << c.z <<  " , " << c.w<<")" << std::endl;

			std::string s = "";
			s = std::string(oss.str());
			stream << s;
			return stream;
		}
	};
}

#endif //TmingEngine_Engine_Math_Vector3_h_