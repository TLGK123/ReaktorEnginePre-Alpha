#include "Hierachy.h"

TmingEngine::Hierachy::~Hierachy()
{
}

void TmingEngine::Hierachy::Begin()
{
}

void TmingEngine::Hierachy::Update()
{
	bool p_open = true;
	ImGui::SetNextWindowSize(ImVec2(350, 560), ImGuiCond_FirstUseEver);
	if (!ImGui::Begin("Hierachy", &p_open))
	{
		ImGui::End();
		return;
	}


	if (ImGui::TreeNode("Basic trees"))
	{
		for (int i = 0; i < 5; i++)
			if (ImGui::TreeNode((void*)(intptr_t)i, "Child %d", i))
			{
				ImGui::Text("blah blah");
				ImGui::SameLine();
				if (ImGui::SmallButton("button")) {};
				ImGui::TreePop();
			}
		ImGui::TreePop();
	}

	ImGui::Text("this is project view");

	ImGui::End();
}

void TmingEngine::Hierachy::End()
{
}
