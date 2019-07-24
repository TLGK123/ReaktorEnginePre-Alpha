#include "SceneView.h"

namespace TmingEngine
{
  


TmingEngine::SceneView::~SceneView()
{
}

void TmingEngine::SceneView::Begin()
{
    
}

void TmingEngine::SceneView::Update()
{
	bool p_open = true;
	ImGui::SetNextWindowSize(ImVec2(650, 370), ImGuiCond_FirstUseEver);
    ImGui::SetNextWindowPos(ImVec2(20, 20));
	if (!ImGui::Begin("Scene", &p_open,ImGuiWindowFlags_NoMove))
	{
		ImGui::End();
		return;
	}

	ImTextureID my_tex_id = (void *)ImageId;
	float my_tex_w = 640;
	float my_tex_h = 360;

	ImGui::Text(" Scene  %.0fx%.0f", my_tex_w, my_tex_h);
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
