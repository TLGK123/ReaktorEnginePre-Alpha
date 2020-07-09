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

#ifndef TmingEngine_Engine_Rending_SoftRender_hpp_
#define TmingEngine_Engine_Rending_SoftRender_hpp_

#include "Core/EngineDefs.h"
#include "Plantform/FileSystem/FileSystem.h"
#include "Rendering/Model.hpp"
#include "Rendering/Primitive.hpp"
#include "Rendering/GouraudShader.hpp"

namespace TmingEngine
{
	ENGINE_CLASS class SoftRender
	{
	public:
		SoftRender() {};
		~SoftRender() {};

		//---------- Simulate  VRAM    Data
		vector<Primitive> primitiveDatas;

		//---------- Simulate  VRAM    Data

		//if we use opegl, we need to load data that like mesh , texture and
		//so on to the VRAM (Vedio Random Access Memory)
		void LoadAssetToMemory()
		{
			Model character(FileSystem::getPath("resources/objects/rock/rock.obj"));
			for (int i = 0; i < character.meshes[0].indices.size(); i += 3)
			{
				int  index1 = character.meshes[0].indices[i];
				int  index2 = character.meshes[0].indices[i + 1];
				int  index3 = character.meshes[0].indices[i + 2];

				Vertex v1 = (character.meshes[0].vertices[index1]);
				Vertex v2 = (character.meshes[0].vertices[index2]);
				Vertex v3 = (character.meshes[0].vertices[index3]);

				Primitive primitive(PrimitiveType::TRIANGLES, vector<Vertex>({ v1,v2,v3 }));
				primitiveDatas.push_back(primitive);
			}
		}

		// spicify the Texture , vertex shader ,fragment shader for each Primitive
		void SetRenderStatus()
		{
			for (int i = 0; i < primitiveDatas.size(); i++)
			{
				primitiveDatas[i].shader = new GouraudShader();
			}
		}

		void DrawCall()
		{
			GenerateFrames();
		}

		// generate one frame mean that we will make one picture ,
		// if we change the picture at the main therad update ,
		// we will get a consecutive game scene
		//
		void GenerateFrames()
		{
		}
	};
} //namespace TmingEngine

#endif //TmingEngine_Engine_Rending_SoftRender_hpp_