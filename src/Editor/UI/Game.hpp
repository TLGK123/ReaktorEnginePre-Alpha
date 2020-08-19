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

#pragma once

#ifndef Game_hpp
#define Game_hpp

#include <stdio.h>

//#include "im.h"

#include "Plantform/Windows/Widget.h"
#include "Plantform/FileSystem/FileSystem.h"

#include "tgaimage/tgaimage.h"

#include "angelscript.h"
#include "scriptstdstring/scriptstdstring.h"
#include "scriptbuilder/scriptbuilder.h"

#include "Core/SubSystem.h"
#include "Core/Context.h"
#include "Core/Math/Vector2.h"
#include "Core/Math/Vector3.h"
#include "Core/Math/Matrix.h"

#include "Rendering/Vertex.hpp"
#include "Rendering/Light.hpp"
#include "Rendering/OpenGL/OpenGLShader.hpp"
#include "Rendering/OpenGL/OpenGLMesh.hpp"
#include "Rendering/SoftRending/SoftRender.hpp"

namespace TmingEngine
{
	class Game :public Widget
	{
	public:

		Game(Context* context)
		{
			m_title = "Game";
		}
		~Game();

		void Begin();
		void Update();
		void End();

		unsigned int imageId;
		SoftRender softRender;
	};
}

#endif