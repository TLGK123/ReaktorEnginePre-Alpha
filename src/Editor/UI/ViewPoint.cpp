#include "ViewPoint.h"

TmingEngine::ViewPoint::~ViewPoint()
{
}

void TmingEngine::ViewPoint::Begin()
{
    
}


void showTransform(Transform * root)
{
    std::vector<Transform *>::iterator ite;
    
    for (ite = root->m_children.begin();ite != root->m_children.end() ; ite++)
    {
        if ((*ite)->m_children.size()>0)
        {
            
            if (ImGui::TreeNode((*ite)->GetGameObject()->name.c_str()))
            {
                if (ImGui::IsItemClicked())
                {
                    Debug::Log("选中--1-父级对象 %s \n",(*ite)->GetGameObject()->name.c_str());
                    Selecttion::activeTransform =  *ite;
                }
                showTransform((*ite)->GetGameObject()->transform);
                ImGui::TreePop();
            }else
            {
                if (ImGui::IsItemClicked())
                {
                    Debug::Log("选中--2-父级对象 %s \n",(*ite)->GetGameObject()->name.c_str());
                    Selecttion::activeTransform =  *ite;
                }
            }
        }else
        {
            
            ImGuiTreeNodeFlags node_flags = ImGuiTreeNodeFlags_OpenOnArrow | ImGuiTreeNodeFlags_OpenOnDoubleClick;
            node_flags |= ImGuiTreeNodeFlags_Leaf | ImGuiTreeNodeFlags_NoTreePushOnOpen;
            int tempIndex = 9 ,node_clicked;
            if( ImGui::TreeNodeEx((void*)(intptr_t)tempIndex, node_flags,(*ite)->GetGameObject()->name.c_str()))
            {
                if (ImGui::IsItemClicked())
                {
                    Debug::Log("选中--末端物体 %s \n",(*ite)->GetGameObject()->name.c_str());
                    Selecttion::activeTransform =  *ite;
                }
                
            }
            
        }
    }
    
    
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
    
    ImGui::BeginChild("left pane", ImVec2(200, 0), true);
    
    auto engine = Global<Context>().GetSubsystem<Engine>();
    auto scene = engine->currentScene;
    if (ImGui::TreeNode(scene->name.c_str()))
    {
        showTransform(scene->SceneRoot->transform);
        ImGui::TreePop();
    }
    
    ImGui::EndChild();
    
    ImGui::SameLine();
    ImGui::SameLine();
    
    ImGui::BeginChild("scene view", ImVec2(0, -ImGui::GetFrameHeightWithSpacing()));
    
	ImTextureID my_tex_id = (void *)ImageId;
	float my_tex_w = 683;
	float my_tex_h = 384;

	ImGui::Text("%.0fx%.0f", my_tex_w, my_tex_h);
	//----------------------------------------------------------------- -1 -1  Image reversal
	ImGui::Image(my_tex_id, ImVec2(my_tex_w, my_tex_h), ImVec2(0, 0), ImVec2(-1, -1), ImColor(255, 255, 255, 255), ImColor(255, 255, 255, 128));

    ImGui::EndChild();
    
   
	ImGui::End();
}

void TmingEngine::ViewPoint::End()
{
}

void TmingEngine::ViewPoint::SetTexture(int Id)
{
	ImageId = Id;
}
