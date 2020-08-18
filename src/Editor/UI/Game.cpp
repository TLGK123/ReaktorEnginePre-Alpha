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

#include "Game.hpp"

namespace TmingEngine
{
	TmingEngine::Game::~Game()
	{
	}

	void TmingEngine::Game::Begin()
	{
		Debug::Log("------Start------Application Stage---------------------------------\n");

		//softRender.LoadAssetToMemory();
		//softRender.SetRenderStatus();
		//softRender.DrawCall();
	}

	void TmingEngine::Game::Update()
	{
		bool p_open = true;
		ImGui::SetNextWindowSize(Vector2(640, 360), ImGuiCond_FirstUseEver);
		if (!ImGui::Begin("Game", &p_open))
		{
			ImGui::End();
			return;
		}
		ImTextureID my_tex_id = (void*)softRender.frameID;
		float my_tex_w = softRender.frameWidth;
		float my_tex_h = softRender.frameHeight;

		ImGui::Text("%.0fx%.0f", my_tex_w, my_tex_h);
		//----------------------------------------------------------------- -1 -1  Image reversal
		ImGui::Image(my_tex_id, Vector2(my_tex_w, my_tex_h), Vector2(0, 0), Vector2(-1, -1), ImColor(255, 255, 255, 255), ImColor(255, 255, 255, 128));
		ImGui::End();
	}

	void TmingEngine::Game::End()
	{
	}
}