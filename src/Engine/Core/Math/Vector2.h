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
#include <iostream>

#include "ImGui/imgui.h"
#include "glm/glm.hpp"

using namespace glm;

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

		Vector2 operator * (const int num) const
		{
			return Vector2(x * num, y * num);
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
