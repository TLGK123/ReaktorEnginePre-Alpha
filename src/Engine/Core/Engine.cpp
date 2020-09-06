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

#include "Engine.h"

namespace TmingEngine
{
	Engine::Engine(Context* context) : Subsystem(context)
	{
	}

	bool Engine::Initialize()
	{
		windows = new ScreenWin(m_context);
		m_sceneManager = new SceneManager();
		m_sceneManager->AllScenes.push_back(new Scene());

		m_context->RegisterSubsystem(this);
		m_context->RegisterSubsystem(windows);

		return true;
	}

	void Engine::Update()
	{
		windows->WinRender();
	}

	void Engine::Destory()
	{
		windows->WinClose();
	}

	void Engine::RenderScene()
	{
		if (m_sceneManager != nullptr && m_sceneManager->AllScenes.size() > 0)
		{
			for (int i = 0; i < m_sceneManager->AllScenes.size(); i++)
			{
				m_sceneManager->AllScenes[i]->Update();
			}
		}
	}

	bool Engine::ShouldClose()
	{
		return windows->WinShouldClose();
	}

	void Engine::SetEngineModeToEditor(bool mode)
	{
		isEditorMode = mode;
		windows->isEditorWindows = mode;
	}
}