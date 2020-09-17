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
		Matrix clip2Object;
		Vector3 light_dir;
		Matrix TBN;

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
			// triangle uv coordinates
	//		varying_uv.push_back(vertex.TexCoords);
			// normal per vertex
	//		varying_nrm.push_back((porjection * view * model).Inverse().Transpose() * vertex.Normal );
			//triangle coordinates (clip coordinates)
	//		Vector4 gl_Vertex = porjection * view * model * vertex.Position;
			//		varying_tri.push_back(gl_Vertex);
					// triangle in normalized device coordinates
	//		Vector3 npos = gl_Vertex / gl_Vertex.w;
	//		ndc_tri.push_back(npos);

			// transform the light vector to the normalized device coordinates

			//定义在世界坐标中的相机基本坐标系   相机空间的坐标 = 世界坐标

			//应用于法线向量的变换矩阵是顶点变换矩阵的逆转置矩阵
			//Matrix normalMatrix = model.Inverse().Transpose();
			//Vector3 T = ((Vector3)(normalMatrix * vertex.Tangent)).Normalize();
			//Vector3 B = ((Vector3)(normalMatrix * vertex.Bitangent)).Normalize();
			//Vector3 N = ((Vector3)(normalMatrix * vertex.Normal)).Normalize();
			//vertex.Position = viewPoint * projection * view * model * vertex.Position;
			//TBN = Matrix(3, 3, {
			//	T.x,B.x,N.x,
			//	T.y,B.y,N.y,
			//	T.z,B.z,N.z,
			//	});

			//light_dir = ((DirectLight*)light)->Direction.Normalize();

			vertex.Position = viewPoint * projection * view * model * vertex.Position;
			viewPos = viewPoint * projection * view * model * viewPos;
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
			//Vector3 bn = vertex.Normal.Normalize();
			//Vector2 uv = vertex.TexCoords;

			//Vector3 v1 = ndc_tri[1] - ndc_tri[0];
			//Vector3 v2 = ndc_tri[2] - ndc_tri[0];

			//Matrix A(3, 3,
			//	{
			//	 v1.x ,v1.y,v1.z,
			//	 v2.x ,v2.y,v2.z,
			//	 bn.x, bn.y, bn.z,
			//	});

			//Matrix AI = A.Inverse();
			//Vector2 delatUV1 = varying_uv[1] - varying_uv[0];
			//Vector2 delatUV2 = varying_uv[2] - varying_uv[0];

			//Vector3 i = AI * Vector3(delatUV1.x, delatUV2.x, 0);
			//Vector3 j = AI * Vector3(delatUV1.y, delatUV2.y, 0);

			//i = i.Normalize();
			//j = j.Normalize();

			//Matrix B = Matrix(3, 3, {
			//	i.x,i.y ,i.z,
			//	j.x,j.y ,j.z,
			//	bn.x,bn.y ,bn.z,
			//	}).Transpose();

			Vector3 Normal = CalcBumpedNormal(vertex);

			Vector3 n = Normal;
			Vector3 l = ((DirectLight*)light)->Direction.Normalize();
			float diff = std::max(l.Dot(n), 0.f);

			//Vector3 viewDir = (viewPos - vertex.Position).Normalize();
			//Vector3 r = (n * (n.Dot(l)) * 2 - l);   // reflected light direction
			//TGAColor specColor = CalcSpecular(vertex);
			//float spec = std::pow(std::max(viewDir.Dot(r), 0.f), 5.0f);

			//Vector3 posInShaowScreen = object2ShadowScreen * clip2Object * vertex.Position;
			//int index = (int)posInShaowScreen.x + (int)posInShaowScreen.y * screenWidth;
			//int shadowDepth = shadowbuffer[index];
			//float tempf = (shadowDepth < posInShaowScreen.z) ? 1 : 0;
			//float shadow = 0.3f + 0.7 * tempf;

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
			//TGAColor specular = specColor * spec;

			color = ambient + diffuse;//+ specular;
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