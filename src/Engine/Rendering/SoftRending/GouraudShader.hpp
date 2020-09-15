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

		int* shadowbuffer = NULL;
		Matrix object2ShadowScreen;
		Matrix frameScreen2Object;
		Vector3 light_dir;

		Vector3 CalcBumpedNormal(TmingEngine::IVertex p)
		{
			int u = p.TexCoords.x * textures[1]->image.get_width();
			int v = p.TexCoords.y * textures[1]->image.get_height();
			TGAColor colorNormal = textures[1]->image.get(u, v);

			Vector3 BumpMapNormal = Vector3(colorNormal[2] * 2 / 255.0f - 1, colorNormal[1] * 2 / 255.0f - 1, colorNormal[0] * 2 / 255.0f - 1);
			return  BumpMapNormal.Normalize();
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
			// triangle uv coordinates
			varying_uv.push_back(vertex.TexCoords);
			// normal per vertex
			varying_nrm.push_back((porjection * view * model).Inverse().Transpose() * vertex.Normal );
			//triangle coordinates (clip coordinates)
			Vector4 gl_Vertex = porjection * view * model * vertex.Position;
			varying_tri.push_back(gl_Vertex);
			// triangle in normalized device coordinates
			Vector3 npos = gl_Vertex / gl_Vertex.w;
			ndc_tri.push_back(npos);
	
			// transform the light vector to the normalized device coordinates
			light_dir =((Vector3)(porjection * view * model * ((DirectLight*)light)->Direction)).Normalize();
			return vertex.Position;
		};

		bool Fragment(TGAColor& color, TmingEngine::IVertex& vertex)override
		{
			Vector3 bn = vertex.Normal.Normalize();
			Vector2 uv = vertex.TexCoords;

			Vector3 v1 = ndc_tri[1] - ndc_tri[0];
			Vector3 v2 = ndc_tri[2] - ndc_tri[0];

			Matrix A(3, 3,
				{
				 v1.x ,v1.y,v1.z,
				 v2.x ,v2.y,v2.z,
				 bn.x, bn.y, bn.z,
				});


			Matrix AI = A.Inverse();
			Vector2 delatUV1 = varying_uv[1] - varying_uv[0];
			Vector2 delatUV2 = varying_uv[2] - varying_uv[0];
			
			Vector3 i = AI * Vector3(delatUV1.x, delatUV2.x, 0);
			Vector3 j = AI * Vector3(delatUV1.y, delatUV2.y, 0);
			
			i = i.Normalize();
			j = j.Normalize();

			Matrix B = Matrix(3, 3, {
				i.x,i.y ,i.z,
				j.x,j.y ,j.z,
				bn.x,bn.y ,bn.z,
				}).Transpose();

			Vector3 Normal = CalcBumpedNormal(vertex);
			Vector3 n = (Vector3(B * Normal)).Normalize(); // transform the normal from the texture to the tangent space
			Vector3 l = light_dir;
			
			float diff = std::max(l.Dot(n), 0.f);
			Vector3 r = (n * (n.Dot(l)) * 2 - l);   // reflected light direction
			TGAColor specColor = CalcSpecular(vertex);
			float spec = std::pow(std::max(r.z, 0.f), 5 + specColor.bgra[0]);

			auto posInShaowScreen = object2ShadowScreen * frameScreen2Object * vertex.Position;
			int index = (int)vertex.Position.x + (int)vertex.Position.y * screenWidth;
			int shadowDepth = shadowbuffer[index];
			float tempf = (shadowDepth < vertex.Position.z) ? 1 : 0;
			if (tempf == 1)
			{
				int c = 0;
			}
			float shadow = 0.3f + 0.7 * tempf;

			int u = vertex.TexCoords.x * textures[0]->image.get_width();
			int v = vertex.TexCoords.y * textures[0]->image.get_height();
			if (vertex.TexCoords.x == 0 && vertex.TexCoords.y == 0)
			{
				color = TGAColor(125, 125, 125, 255);
				return false;
			}
			else
			{
				color = textures[0]->image.get(u, v);
			}

			for (int i = 0; i < 3; i++)
			{
				color[i] = std::min(10 + color[i]+(diff * spec),255.0f);
			}

			return false;
		}



		Vector3 GouraudShader::Vertex(Vector3 pos)
		{
			return Vector3();
		}

		bool GouraudShader::Fragment(TGAColor& color, Vector3 barycent)
		{
			return false;
		}

		bool GouraudShader::Fragment(TGAColor& color)
		{
			return false;
		}

};
}

#endif //TmingEngine_Engine_Rending_GouraudShader_hpp_