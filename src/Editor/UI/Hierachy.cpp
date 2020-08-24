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

#include "Hierachy.hpp"

namespace TmingEngine
{
	Hierachy::~Hierachy()
	{
	}

	void Hierachy::Begin()
	{
	}

	void showTransform(Transform* root)
	{
		std::vector<Transform*>::iterator ite;

		for (ite = root->m_children.begin(); ite != root->m_children.end(); ite++)
		{
			if ((*ite)->m_children.size() > 0)
			{
				if (ImGui::TreeNode((*ite)->GetGameObject()->name.c_str()))
				{
					if (ImGui::IsItemClicked())
					{
						Debug::Log("选中--1-父级对象 %s \n", (*ite)->GetGameObject()->name.c_str());
						Selecttion::activeTransform = *ite;
					}
					showTransform((*ite)->GetGameObject()->transform);
					ImGui::TreePop();
				}
				else
				{
					if (ImGui::IsItemClicked())
					{
						Debug::Log("选中--2-父级对象 %s \n", (*ite)->GetGameObject()->name.c_str());
						Selecttion::activeTransform = *ite;
					}
				}
			}
			else
			{
				ImGuiTreeNodeFlags node_flags = ImGuiTreeNodeFlags_OpenOnArrow | ImGuiTreeNodeFlags_OpenOnDoubleClick;
				node_flags |= ImGuiTreeNodeFlags_Leaf | ImGuiTreeNodeFlags_NoTreePushOnOpen;
				int tempIndex = 9, node_clicked;
				if (ImGui::TreeNodeEx((void*)(intptr_t)tempIndex, node_flags, (*ite)->GetGameObject()->name.c_str()))
				{
					if (ImGui::IsItemClicked())
					{
						Debug::Log("选中--末端物体 %s \n", (*ite)->GetGameObject()->name.c_str());
						Selecttion::activeTransform = *ite;
					}
				}
			}
		}
	}

	void Hierachy::Update()
	{
		bool p_open = true;
		ImGui::SetNextWindowSize(ImVec2(350, 560), ImGuiCond_FirstUseEver);
		if (!ImGui::Begin("Hierachy", &p_open))
		{
			ImGui::End();
			return;
		}

		auto engine = Global<Context>().GetSubsystem<Engine>();
		auto scene = engine->currentScene;
		if (ImGui::TreeNode("test"))
		{
			showTransform(scene->SceneRoot->transform);
			ImGui::TreePop();
		}

		ImGui::End();
	}

	void Hierachy::End()
	{
	}
}