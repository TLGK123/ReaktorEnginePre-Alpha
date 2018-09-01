#include "ViewPoint.h"

TmingEngine::ViewPoint::~ViewPoint()
{
}

void TmingEngine::ViewPoint::Begin()
{

}

void TmingEngine::ViewPoint::Update()
{
	bool p_open = true;
	ImGui::SetNextWindowSize(ImVec2(350, 560), ImGuiCond_FirstUseEver);
	if (!ImGui::Begin("Scene", &p_open))
	{
		ImGui::End();
		return;
	}

	ImTextureID my_tex_id = (void *)ImageId;
	float my_tex_w = 1024;
	float my_tex_h = 576;

	ImGui::Text("%.0fx%.0f", my_tex_w, my_tex_h);
	//----------------------------------------------------------------- -1 -1  Image reversal
	ImGui::Image(my_tex_id, ImVec2(my_tex_w, my_tex_h), ImVec2(0, 0), ImVec2(-1, -1), ImColor(255, 255, 255, 255), ImColor(255, 255, 255, 128));

	ImGui::End();

}

void TmingEngine::ViewPoint::End()
{

}

void TmingEngine::ViewPoint::SetTexture(int Id)
{
	ImageId = Id;
}