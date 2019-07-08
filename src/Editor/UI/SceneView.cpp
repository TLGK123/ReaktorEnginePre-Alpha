#include "SceneView.h"

namespace TmingEngine
{
  


TmingEngine::SceneView::~SceneView()
{
}

void TmingEngine::SceneView::Begin()
{
    
}

extern  void showTransform(Transform * root);
    
void TmingEngine::SceneView::Update()
{
	bool p_open = true;
	ImGui::SetNextWindowSize(ImVec2(350, 560), ImGuiCond_FirstUseEver);
	if (!ImGui::Begin("Scene", &p_open))
	{
		ImGui::End();
		return;
	}
    
    ImGui::BeginChild("left pane", ImVec2(200, 0), true);
    
//    auto engine = Global<Context>().GetSubsystem<Engine>();
//    auto scene = engine->currentScene;
//    if (scene != NULL &&  ImGui::TreeNode(scene->name.c_str()))
//    {
//        showTransform(scene->SceneRoot->transform);
//        ImGui::TreePop();
//    }
    
    ImGui::EndChild();
    
    ImGui::SameLine();
//    ImGui::SameLine();
    
    ImGui::BeginChild("scene view", ImVec2(0, -ImGui::GetFrameHeightWithSpacing()));
	ImTextureID my_tex_id = (void *)ImageId;
	float my_tex_w = 683;
	float my_tex_h = 384;

	ImGui::Text(" Scene  %.0fx%.0f", my_tex_w, my_tex_h);
	//----------------------------------------------------------------- -1 -1  Image reversal
	ImGui::Image(my_tex_id, ImVec2(my_tex_w, my_tex_h), ImVec2(0, 0), ImVec2(-1, -1), ImColor(255, 255, 255, 255), ImColor(255, 255, 255, 128));

    ImGui::EndChild();
    
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
