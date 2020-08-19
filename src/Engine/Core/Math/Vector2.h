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

#ifndef TmingEngine_Engine_Math_Vector2_h_
#define TmingEngine_Engine_Math_Vector2_h_

#include <stdio.h>
#include <string>
#include <sstream>
#include <iostream>
#include <iomanip>

#include "Core/EngineDefs.h"
#include "Core//Math/MathFunctions.hpp"
#include "ImGui/imgui.h"

using namespace glm;
using namespace std;
namespace TmingEngine
{
	ENGINE_CLASS class Vector2
	{
	public:
		float x = 0;
		float y = 0;

		Vector2()
		{
		}

		//We don't want to modify the class member value ,if a function add "const" at the end,
		//it mesans that the function will not change the object property
		//if the parameter add a "const ",it means that the function can pass a const parameter or not,
		//and the parameter will not be changed in the fucntion.

		Vector2 operator - (const Vector2& v) const
		{
			return Vector2(x - v.x, y - v.y);
		}

		Vector2 operator + (const Vector2& v) const
		{
			return Vector2(x + v.x, y + v.y);
		}

		Vector2 operator * (const float num) const
		{
			return Vector2(x * num, y * num);
		}

		friend ostream& operator<<(ostream& stream, const Vector2 c)
		{
			ostringstream oss;
			oss << setiosflags(ios::fixed | ios::right) << setw(8) << setprecision(2) << "(" << c.x << " , " << c.y << ")" << endl;

			std::string s = "";
			s = string(oss.str());
			stream << s;
			return stream;
		}

		//对应的组件值，相乘并相加,通常用于计算向量的夹角
		// A * B = |A|*|B|*Cos(θ)=(a1*b1 + a2*b2 + ... + an*bn)
		float Dot(Vector2& v)
		{
			return  x * v.x + y * v.y;
		}

		//斜对角相乘 并相减
		float Cross(Vector2& v)
		{
			return  x * v.y - v.x * y;
		}

		Vector2(float x, float y)
		{
			this->x = x;
			this->y = y;
		}

		Vector2(vec2 v2)
		{
			this->x = v2.x;
			this->y = v2.y;
		}

		operator ImVec2()
		{
			return ImVec2(x, y);
		}

		operator vec2()
		{
			return vec2(x, y);
		}

		static const Vector2 Zero;
		static const Vector2 One;
	};
}

#endif //TmingEngine_Engine_Math_Vector2_h_