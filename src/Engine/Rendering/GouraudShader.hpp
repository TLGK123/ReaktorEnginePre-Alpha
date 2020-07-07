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

#ifndef TmingEngine_Engine_Rending_GouraudShader_hpp_
#define TmingEngine_Engine_Rending_GouraudShader_hpp_

#include "Core/Math/Vector3.h"
#include "Core/Math/Matrix.h"
#include "IShader.hpp"

namespace TmingEngine
{
	class GouraudShader :public IShader
	{
	public:
		GouraudShader() {};
		~GouraudShader() {};

		Vector3 Vertex(Vector3 pos) override
		{
			Matrix p1(4, 1,
				{
				  pos.x,
				  pos.y,
				  pos.z,
				  1,
				});

			auto projectionPoint1 = porjection * view * model * p1;
			float w1 = projectionPoint1[3][0];
			Matrix t1(4, 4,
				{
				1 / w1 , 0 , 0 , 0 ,
				0 , 1 / w1 , 0 , 0 ,
				0 , 0 , 1 / w1 , 0 ,
				0 , 0 , 0 , 1 / w1 ,
				});

			//Í¸ÊÓ³ý·¨

			auto point1 = viewPoint * t1 * projectionPoint1;

			return Vector3(point1[0][0], point1[1][0], point1[2][0]);
		};

		bool Fragment(TGAColor& color, Vector3 barycent)override
		{
			//color = TGAColor(125,125,125,255);
			return false;
		}

		bool Fragment(TGAColor& color)override
		{
			//color = TGAColor(125,125,125,255);
			return false;
		}
	};
}

#endif //TmingEngine_Engine_Rending_GouraudShader_hpp_