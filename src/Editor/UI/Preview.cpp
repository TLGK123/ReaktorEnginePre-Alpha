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

#include "Preview.hpp"

namespace TmingEngine
{
	Preview::~Preview()
	{
	}

	void Preview::Begin()
	{
		p_open = true;
		auto context = &Global<Context>();
		Engine* eg = context->GetSubsystem<Engine>();
		auto softRender = eg->m_softRender;
		ImageId = softRender->depthID;
	}

	void Preview::Update()
	{
		if (!p_open)
		{
			return;
		}
		ImGui::SetNextWindowSize(ImVec2(640, 360), ImGuiCond_FirstUseEver);
		if (!ImGui::Begin("Preview", &p_open))
		{
			ImGui::End();
			return;
		}
		ImTextureID my_tex_id = (void*)ImageId;
		int my_tex_w = ImGui::GetWindowSize().x - 20;
		int my_tex_h = ImGui::GetWindowSize().y - 50;

		//----------------------------------------------------------------- -1 -1  Image reversal

		ImGui::Image(my_tex_id, ImVec2(my_tex_w, my_tex_h), ImVec2(0, 0), ImVec2(-1, -1), ImColor(255, 255, 255, 255), ImColor(255, 255, 255, 128));
		ImGui::End();
	}

	void Preview::End()
	{
	}

	void Preview::PreviewTexture(std::string path)
	{
		OpenGLTexture* ot = new OpenGLTexture();
		ImageId = ot->LoadTexture(path.c_str());
	}
}// namespace TmingEngine