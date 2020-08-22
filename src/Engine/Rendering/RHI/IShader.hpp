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

#ifndef TmingEngine_Engine_Rending_IShader_hpp_
#define TmingEngine_Engine_Rending_IShader_hpp_

#include "Core/Math/Vector3.h"
#include "Core/Math/Matrix.h"

#include "tgaimage/tgaimage.h"

#include "Rendering/Vertex.hpp"
#include "Rendering/RHI/ITexture.hpp"
#include "Rendering/Light.hpp"

namespace TmingEngine
{
	class IShader
	{
	public:

		IShader() {};
		~IShader() {};

		int ID = 0;
		Matrix porjection;
		Matrix view;
		Matrix model;
		Matrix viewPoint;

		vector<ITexture*> textures;

		ILight* light;

		void SetProjection(Matrix p)
		{
			porjection = p;
		}

		void SetView(Matrix v)
		{
			view = v;
		}

		void SetModel(Matrix m)
		{
			model = m;
		}

		void SetViewPoint(Matrix vp)
		{
			viewPoint = vp;
		}

		virtual Vector3 Vertex(Vector3 pos) = 0;
		virtual Vector3 Vertex(TmingEngine::Vertex& vertex) = 0;
		virtual bool Fragment(TGAColor& color, Vector3 barycent) = 0;
		virtual bool Fragment(TGAColor& color) = 0;
		virtual bool Fragment(TGAColor& color, TmingEngine::Vertex& vertex) = 0;
	};
}

#endif //TmingEngine_Engine_Rending_IShader_hpp_