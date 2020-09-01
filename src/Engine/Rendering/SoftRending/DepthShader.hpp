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

#ifndef TmingEngine_Engine_Rending_DepthShader_hpp_
#define TmingEngine_Engine_Rending_DepthShader_hpp_

#include "Core/Log.h"
#include "Core/Math/Vector3.h"
#include "Core/Math/Matrix.h"
#include "Rendering/RHI/IShader.hpp"

namespace TmingEngine
{
	class DepthShader :public IShader
	{
	public:
		DepthShader() {};
		~DepthShader() {};

		Matrix TBN;

		Vector3 Vertex(Vector3 pos) override
		{
			auto projectionPoint = porjection * view * model * pos;
			float w = projectionPoint[3][0];
			Matrix t1(4, 4,
				{
				1 / w , 0 , 0 , 0 ,
				0 , 1 / w , 0 , 0 ,
				0 , 0 , 1 / w , 0 ,
				0 , 0 , 0 , 1 / w ,
				});

			auto ndcPoint = viewPoint * t1 * projectionPoint;

			return Vector3(ndcPoint[0][0], ndcPoint[1][0], ndcPoint[2][0]);
		};

		Vector3 Vertex(TmingEngine::IVertex& vertex) override
		{
			auto projectionPoint = porjection * view * model * vertex.Position;
			float w = projectionPoint[3][0];
			Matrix t1(4, 4,
				{
				1 / w , 0 , 0 , 0 ,
				0 , 1 / w , 0 , 0 ,
				0 , 0 , 1 / w , 0 ,
				0 , 0 , 0 , 1 / w ,
				});

			//std::cout << projectionPoint << std::endl;

			auto screenPoint = viewPoint * t1 * projectionPoint;

			vertex.Position = screenPoint;
			return screenPoint;
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

		bool Fragment(TGAColor& color, TmingEngine::IVertex& vertex)override
		{
			float f = 255 - vertex.Position.z;
			//Debug::Log(std::to_string(vertex.Position.z));
			color = TGAColor(f, f, f);
			return false;
		}
	};
}

#endif //TmingEngine_Engine_Rending_DepthShader_hpp_