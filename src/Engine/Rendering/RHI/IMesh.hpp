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

#ifndef TmingEngine_Engine_Rending_RHI_IMesh_hpp_
#define TmingEngine_Engine_Rending_RHI_IMesh_hpp_

#include "Rendering/RHI/IShader.hpp"
using namespace std;

namespace TmingEngine
{
	class IMesh {
	public:
		IMesh() {}

		vector<IVertex> vertices;
		vector<unsigned int> indices;
		vector<ITexture*> textures;

		unsigned int id = 0;
		virtual void LoadMesh(const char* path) = 0;
		virtual void Draw(IShader* shader) = 0;
	};
}

#endif /* TmingEngine_Engine_Rending_IMesh_hpp_ */