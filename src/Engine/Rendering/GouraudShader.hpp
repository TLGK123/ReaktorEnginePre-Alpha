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

			//透视除法

			auto ndcPoint = viewPoint * t1 * projectionPoint;

			return Vector3(ndcPoint[0][0], ndcPoint[1][0], ndcPoint[2][0]);
		};

		Vector3 Vertex(TmingEngine::Vertex& vertex) override
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

			//透视除法

			auto ndcPoint = viewPoint * t1 * projectionPoint;

			return Vector3(ndcPoint[0][0], ndcPoint[1][0], ndcPoint[2][0]);
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

		bool Fragment(TGAColor& color, TmingEngine::Vertex& vertex)override
		{
			int u = vertex.TexCoords.x * textures[0].image.get_width();
			int v = vertex.TexCoords.y * textures[0].image.get_height();
			color = textures[0].image.get(u, v);

			Vector3 Normal = CalcBumpedNormal(vertex);

			float intensity = light.Direction.Dot(Normal);
			if (intensity > 0)
			{
				color = color * intensity;
				return false;
			}
			else
			{
				return true;
			}
		}

		Vector3 CalcBumpedNormal(TmingEngine::Vertex p)
		{
			Vector3 Normal = p.Normal.Normalize();
			Vector3 Tangent = p.Tangent.Normalize();
			Tangent = (Normal.Cross(Tangent - Tangent.Dot(Normal))).Normalize();
			Vector3 Bitangent = Tangent.Cross(Normal);

			int u = p.TexCoords.x * textures[0].image.get_width();
			int v = p.TexCoords.y * textures[0].image.get_height();
			TGAColor colorNormal = textures[1].image.get(u, v);
			Vector3 BumpMapNormal = Vector3(colorNormal[2] / 255.0f, colorNormal[1] / 255.0f, colorNormal[0] / 255.0f);
			BumpMapNormal = BumpMapNormal.Normalize();
			BumpMapNormal = BumpMapNormal * 2 - Vector3(1, 1, 1);

			Vector3 NewNormal;
			Matrix TBN = Matrix(3, 3, {
				Tangent.x ,Tangent.y,Tangent.z,
				Bitangent.x ,Bitangent.y,Bitangent.z,
				Normal.x,Normal.y,Normal.z });
			NewNormal = TBN * Matrix(3, 1, { BumpMapNormal.x,BumpMapNormal.y,BumpMapNormal.z });
			NewNormal = NewNormal.Normalize();
			return NewNormal;
		}
	};
}

#endif //TmingEngine_Engine_Rending_GouraudShader_hpp_