//
//
//

#include "Preview.hpp"
TmingEngine::Preview::~Preview()
{
}

void TmingEngine::Preview::Begin()
{
	p_open = true;
}

void TmingEngine::Preview::Update()
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
    ImTextureID my_tex_id = (void *)ImageId;
    float my_tex_w = ImGui::GetWindowSize().x-35;
    float my_tex_h = ImGui::GetWindowSize().y-35;
    //----------------------------------------------------------------- -1 -1  Image reversal
    ImGui::Image(my_tex_id, ImVec2(my_tex_w, my_tex_h), ImVec2(0, 0), ImVec2(-1, -1), ImColor(255, 255, 255, 255), ImColor(255, 255, 255, 128));
    ImGui::End();
}

void TmingEngine::Preview::End()
{
}
