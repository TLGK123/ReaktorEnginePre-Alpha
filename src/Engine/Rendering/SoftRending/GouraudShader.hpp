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
#include "Rendering/RHI/IShader.hpp"

namespace TmingEngine
{
	class GouraudShader :public IShader
	{
	public:
		GouraudShader() {};
		~GouraudShader() {};

		float* shadowbuffer = NULL;
		Matrix object2ShadowScreen;
		Matrix world2Object;
		Vector3 light_dir;
		Matrix TBN;
		TGAImage* depthFind = NULL;
		Vector3 viewPos;

		Vector3 CalcBumpedNormal(TmingEngine::IVertex p)
		{
			Vector3 Normal = ((Vector3)(p.Normal)).Normalize();
			Vector3 Tangent = ((Vector3)(p.Tangent - p.Normal * p.Normal.Dot(p.Tangent))).Normalize();
			Vector3 Bitangent = ((Vector3)((Normal.Cross(Tangent)))).Normalize();

			int u = p.TexCoords.x * textures[1]->image.get_width();
			int v = p.TexCoords.y * textures[1]->image.get_height();
			TGAColor colorNormal = textures[1]->image.get(u, v);
			Vector3 BumpMapNormal = Vector3(colorNormal[2] / 255.0f, colorNormal[1] / 255.0f, colorNormal[0] / 255.0f);
			BumpMapNormal = BumpMapNormal.Normalize();
			BumpMapNormal = BumpMapNormal * 2 - Vector3(1, 1, 1);

			Vector3 NewNormal;
			Matrix TBN = Matrix(3, 3, {
				Tangent.x ,  Bitangent.x , Normal.x ,
				Tangent.y ,  Bitangent.y,  Normal.y ,
				Tangent.z ,  Bitangent.z , Normal.z });
			NewNormal = TBN * Matrix(3, 1, { BumpMapNormal.x,BumpMapNormal.y,BumpMapNormal.z });
			NewNormal = NewNormal.Normalize();
			return NewNormal;
		}

		TGAColor CalcSpecular(TmingEngine::IVertex p)
		{
			int u = p.TexCoords.x * textures[2]->image.get_width();
			int v = p.TexCoords.y * textures[2]->image.get_height();
			TGAColor specColor = textures[2]->image.get(u, v);
			return specColor;
		}

		Vector3 Vertex(TmingEngine::IVertex& vertex) override
		{
			Matrix mvpv = viewPoint * projection * view * model;
			vertex.FragPos = model * vertex.Position;  //world
			vertex.Position = mvpv * vertex.Position;

			Matrix normalMatrix = modelIT;

			Vector3 Normal = ((Vector3)(normalMatrix * vertex.Normal)).Normalize();
			Vector3 Tangent = ((Vector3)(normalMatrix * vertex.Tangent)).Normalize();
			Vector3 Bitangent = ((Vector3)(normalMatrix * (Normal.Cross(Tangent)))).Normalize();

			vertex.Normal = Normal;
			vertex.Tangent = Tangent;
			vertex.Bitangent = Bitangent;

			return vertex.Position;
		};

		bool Fragment(TGAColor& color, TmingEngine::IVertex& vertex)override
		{
			Vector3 Normal = CalcBumpedNormal(vertex);

			Vector3 n = Normal;
			Vector3 l = ((DirectLight*)light)->Direction.Normalize();
			float diff = std::max(l.Dot(n), 0.f);

			Vector3 viewDir = (viewPos - vertex.FragPos).Normalize();
			Vector3 r = (n * (n.Dot(l)) * 2 - l).Normalize();   // reflected light direction
			TGAColor specColor = CalcSpecular(vertex);
			float spec = std::pow(std::max(viewDir.Dot(r), 0.f), 5);

			Vector3 posInShaowScreen = object2ShadowScreen * world2Object * vertex.FragPos;
			int index = (int)(posInShaowScreen.x + posInShaowScreen.y * screenWidth);
			float pixelDepth = posInShaowScreen.z;
			float shadowDepth = shadowbuffer[index];
			float tempf = 1;

			if (pixelDepth - 2 <= shadowDepth)
			{
				depthFind->set(posInShaowScreen.x, posInShaowScreen.y, TGAColor(255, 0, 0));
				tempf = 1;
			}
			else
			{
				depthFind->set(posInShaowScreen.x, posInShaowScreen.y, TGAColor(0, 255, 0));
				tempf = 0;
			}
			float shadow = 0.1f + 0.9 * tempf;

			int u = vertex.TexCoords.x * textures[0]->image.get_width();
			int v = vertex.TexCoords.y * textures[0]->image.get_height();
			if (vertex.TexCoords.x == 0 && vertex.TexCoords.y == 0)
			{
				color = TGAColor(255, 0, 0, 255);
				return false;
			}
			else
			{
				color = textures[0]->image.get(u, v);
			}
			// Ambient
			TGAColor ambient = color * 0.1;
			TGAColor diffuse = color * diff;
			TGAColor specular = specColor * spec;

			for (int i = 0; i < 3; i++)
			{
				color[i] = std::min<float>(20 + diffuse[i] * shadow * 1.2f + specular[i] * 0.6f, 255);
			}

			if (tempf == 0)
			{
				color = TGAColor(0, 255, 0, 255);
			}
			return false;
		}

		Vector3 Vertex(Vector3 pos)
		{
			return Vector3();
		}

		bool Fragment(TGAColor& color, Vector3 barycent)
		{
			return false;
		}

		bool Fragment(TGAColor& color)
		{
			return false;
		}
	};
}

#endif //TmingEngine_Engine_Rending_GouraudShader_hpp_
