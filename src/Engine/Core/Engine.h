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

#ifndef TmingEngine_Engine_Core_Engine_hpp_
#define TmingEngine_Engine_Core_Engine_hpp_

#define ENGINE_VERSION "v0.0.1"
#define TmengineLib

#include <memory>

#include "Context.h"
#include "Scene/Scene.hpp"
#include "Plantform/Windows/IWindows.h"
#include "Plantform/Windows/win/ScreenWin.h"
#include "Plantform/Time/Timer.h"

#include "GameObject.hpp"
#include "Log/Log.h"

namespace TmingEngine
{
	class Timer;

	class ENGINE_CLASS Engine : public Subsystem
	{
	public:

		Engine(Context* context);

		bool Initialize() override;

		void InitializeWin();

		void Update();

		void Destory();

		void RenderScene();

		bool ShouldClose();

		bool isEditorMode = false;

		void SetEngineModeToEditor(bool mode);

		Context* GetContext() { return m_context; }

		Scene* currentScene;

		IWindows* windows;
	private:

		Timer* m_timer;
	};
}

#endif //TmingEngine_Engine_Core_Engine_hpp_