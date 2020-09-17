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
		auto context = &Global<Context>();
		Engine* eg = context->GetSubsystem<Engine>();
		softRender = eg->m_softRender;
		softRender->LoadAssetToMemory();
		softRender->SetRenderStatus();
		softRender->DrawCall();
	}

	void TmingEngine::Game::Update()
	{
		bool p_open = true;
		ImGui::SetNextWindowSize(Vector2(640, 640), ImGuiCond_FirstUseEver);
		if (!ImGui::Begin("Game", &p_open))
		{
			ImGui::End();
			return;
		}
		ImTextureID my_tex_id = (void*)softRender->frameID;
		float my_tex_w = softRender->frameWidth;
		float my_tex_h = softRender->frameHeight;
		ImVec2 pos = ImGui::GetCursorScreenPos();
		ImVec4 tint_col = ImVec4(1.0f, 1.0f, 1.0f, 1.0f);   // No tint
		ImVec4 border_col = ImVec4(1.0f, 1.0f, 1.0f, 0.5f); // 50% opaque white
		ImGui::Text("%.0fx%.0f", my_tex_w, my_tex_h);
		//----------------------------------------------------------------- -1 -1  Image reversal
		ImGui::Image(my_tex_id, Vector2(my_tex_w, my_tex_h), Vector2(0, 0), Vector2(-1, -1), ImColor(255, 255, 255, 255), ImColor(255, 255, 255, 128));
		ImGuiIO& io = ImGui::GetIO();
		if (ImGui::IsItemHovered())
		{
			ImGui::BeginTooltip();
			float region_sz = 32.0f;
			float region_x = io.MousePos.x - pos.x - region_sz * 0.5f;
			float region_y = io.MousePos.y - pos.y - region_sz * 0.5f;
			float zoom = 4.0f;
			if (region_x < 0.0f) { region_x = 0.0f; }
			else if (region_x > my_tex_w - region_sz) { region_x = my_tex_w - region_sz; }
			if (region_y < 0.0f) { region_y = 0.0f; }
			else if (region_y > my_tex_h - region_sz) { region_y = my_tex_h - region_sz; }
			ImGui::Text("Min: (%.2f, %.2f)", region_x, region_y);
			ImGui::Text("Max: (%.2f, %.2f)", region_x + region_sz, region_y + region_sz);

			ImVec2 uv0 = ImVec2(1.0f - (region_x) / my_tex_w, 1.0f - (region_y) / my_tex_h);
			ImVec2 uv1 = ImVec2(1.0f - (region_x + region_sz) / my_tex_w, 1.0f - (region_y + region_sz) / my_tex_h);

			ImGui::Image(my_tex_id, ImVec2(region_sz * zoom, region_sz * zoom), uv0, uv1, tint_col, border_col);
			ImGui::EndTooltip();
		}

		ImGui::End();
	}

	void TmingEngine::Game::End()
	{
	}
}