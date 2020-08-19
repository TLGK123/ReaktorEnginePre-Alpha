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

#ifndef IMODEL_H
#define IMODEL_H

#include "assimp/Importer.hpp"
#include "assimp/scene.h"
#include "assimp/postprocess.h"

#include "Rendering/OpenGL/OpenGLFunctions.hpp"
#include "Rendering/RHI/ITexture.hpp"
#include "Rendering/RHI/IMesh.hpp"
#include "Rendering/RHI/IShader.hpp"

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <map>
#include <vector>
using namespace std;
namespace TmingEngine
{
	class IModel
	{
	public:
		vector<ITexture*> textures_loaded;
		vector<IMesh*> meshes;
		string directory;
		bool gammaCorrection;

		IModel()
		{
			gammaCorrection = false;
		}

		IModel(string const& path, bool gamma = false)
		{
			gammaCorrection = gamma;
			Init(path);
		}

		virtual void Init(string const& path) = 0;
		virtual void Draw(IShader* shader) = 0;

	private:

		virtual void loadModel(string const& path) = 0;
		virtual void  processNode(aiNode* node, const aiScene* scene) = 0;
		virtual IMesh* processMesh(aiMesh* mesh, const aiScene* scene) = 0;
		virtual vector<ITexture*> loadMaterialTextures(aiMaterial* mat, aiTextureType type, string typeName) = 0;
	};
} // namespace TmingEngine

#endif