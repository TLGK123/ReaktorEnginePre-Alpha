#include "Test.h"

void TestDemo::Render_SceneObject()
{
}

void Demo1::Render_SceneObject()
{
	bool p_open = true;
	//ImGui::SetNextWindowPos(ImVec2(200, 10));
	ImGui::SetNextWindowSize(ImVec2(100, 100), ImGuiCond_FirstUseEver);
	if (!ImGui::Begin("Demo1", &p_open))
	{
		ImGui::End();
		return;
	}
	ImGui::End();
}

void Demo2::Render_SceneObject()
{
	bool p_open = true;
	//ImGui::SetNextWindowPos(ImVec2(200, 10));
	ImGui::SetNextWindowSize(ImVec2(110, 110), ImGuiCond_FirstUseEver);
	if (!ImGui::Begin("Demo2", &p_open))
	{
		ImGui::End();
		return;
	}
	ImGui::End();
}