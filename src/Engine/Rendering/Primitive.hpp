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

#ifndef TmingEngine_Engine_Rending_Primitive_hpp_
#define TmingEngine_Engine_Rending_Primitive_hpp_

#include "Core/EngineDefs.h"
#include "Rendering/Model.hpp"
#include "Plantform/FileSystem/FileSystem.h"
#include "Rendering/IShader.hpp"

namespace TmingEngine
{
	enum PrimitiveType
	{
		POINTS,
		LINES,
		TRIANGLES,
	};

	ENGINE_CLASS class Primitive
	{
	public:
		PrimitiveType	primitiveType;
		vector<Vertex>	poins;
		IShader* shader;

		Primitive()
		{
		}

		Primitive(PrimitiveType pt, vector<Vertex> manyPoints)
		{
			primitiveType = pt;
			poins = manyPoints;
		}

		void CaculateTBN()
		{
			Vector3 Edge1 = poins[1].Position - poins[0].Position;
			Vector3 Edge2 = poins[2].Position - poins[0].Position;

			float DeltaU1 = poins[1].TexCoords.x - poins[0].TexCoords.x;
			float DeltaV1 = poins[1].TexCoords.y - poins[0].TexCoords.y;

			float DeltaU2 = poins[2].TexCoords.x - poins[0].TexCoords.x;
			float DeltaV2 = poins[2].TexCoords.y - poins[0].TexCoords.y;

			float f = 1.0f / (DeltaU1 * DeltaV2 - DeltaU2 * DeltaV1);

			Vector3 Tangent, Bitangent;
			Tangent.x = f * (DeltaV2 * Edge1.x - DeltaV1 * Edge2.x);
			Tangent.y = f * (DeltaV2 * Edge1.y - DeltaV1 * Edge2.y);
			Tangent.z = f * (DeltaV2 * Edge1.z - DeltaV1 * Edge2.z);

			Bitangent.x = f * (-DeltaU2 * Edge1.x - DeltaU1 * Edge2.x);
			Bitangent.y = f * (-DeltaU2 * Edge1.y - DeltaU1 * Edge2.y);
			Bitangent.z = f * (-DeltaU2 * Edge1.z - DeltaU1 * Edge2.z);

			for (int i = 0; i < poins.size(); i++)
			{
				poins[i].Tangent = Tangent.Normalize();
				poins[i].Bitangent = Bitangent.Normalize();
			}
		}

		void VertexShader()
		{
			for (int i = 0; i < poins.size(); i++)
			{
				shader->Vertex(poins[i]);
			}
		}

		//
		void TessellationShader()
		{
		}

		void GeometryShader()
		{
		}
	};
} //namespace TmingEngine

#endif //TmingEngine_Engine_Rending_Primitive_hpp_