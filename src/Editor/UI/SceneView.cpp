/*
            This file is part of: 
                TmingEngine
            https://github.com/xiaomingfun/TmingEngine

   Copyright 2016 - 2020 TmingEngine(NoahGameFrame)

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


#include "SceneView.h"

namespace TmingEngine
{
  


TmingEngine::SceneView::~SceneView()
{
}

void TmingEngine::SceneView::Begin()
{
    
}

int lastSceneX = -1;
int lastSceneY = -1;

void TmingEngine::SceneView::Update()
{
	bool p_open = true;
	ImGui::SetNextWindowSize(ImVec2(650, 375), ImGuiCond_FirstUseEver);
	if (!ImGui::Begin("Scene", &p_open))
	{
		ImGui::End();
		return;
	}
	IsSceneviewFoucsed = ImGui::IsWindowFocused();
	ImTextureID my_tex_id = (void *)ImageId;
	float my_tex_w = ImGui::GetWindowSize().x - 0;
	float my_tex_h = ImGui::GetWindowSize().y - 0;

	//ImGui::Text(" Scene  %.0fx%.0f", my_tex_w, my_tex_h);

	auto s = ImGui::GetWindowViewport();
	//if (lastSceneX != my_tex_w || lastSceneY != my_tex_h)
	//{
	//	if (lastSceneX != -1 || lastSceneY != -1)
	//	{
	//		Global<Context>().GetSubsystem<ScreenSystem>()->SetViewPoint(s->Pos.x, s->Pos.y, s->Size.x, s->Size.y);
	//	}

	//	lastSceneX = my_tex_w;
	//	lastSceneY = my_tex_h;
	//}
	Global<Context>().GetSubsystem<Engine>()->windows->SetViewPoint(s->Pos.x, s->Pos.y, s->Size.x, s->Size.y);
	//----------------------------------------------------------------- -1 -1  Image reversal
	ImGui::Image(my_tex_id, ImVec2(my_tex_w, my_tex_h), ImVec2(0, 0), ImVec2(-1, -1), ImColor(255, 255, 255, 255), ImColor(255, 255, 255, 128));
	ImGui::End();
}

void TmingEngine::SceneView::End()
{
}

void TmingEngine::SceneView::SetTexture(int Id)
{
	ImageId = Id;
}
    
}
