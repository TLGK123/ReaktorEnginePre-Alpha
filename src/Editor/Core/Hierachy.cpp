#include "Hierachy.h"
namespace TmingEngine
{
    TmingEngine::Hierachy::~Hierachy()
    {
    }
    
    void TmingEngine::Hierachy::Begin()
    {
    }
    
    
    void showTransform(Transform * root)
    {
        std::vector<Transform *>::iterator ite;
        for (ite = root->m_children.begin();ite != root->m_children.end() ; ite++) {
            if ((*ite)->m_children.size()>0)
            {
                ImGuiTreeNodeFlags node_flags = ImGuiTreeNodeFlags_OpenOnArrow | ImGuiTreeNodeFlags_OpenOnDoubleClick;
                node_flags |= ImGuiTreeNodeFlags_Leaf | ImGuiTreeNodeFlags_NoTreePushOnOpen;
                int tempIndex = 9 ,node_clicked;
                bool node_open = ImGui::TreeNodeEx((void*)(intptr_t)tempIndex, node_flags,(*ite)->GetGameObject()->name.c_str());
                if (ImGui::IsItemClicked())
                {
                    node_clicked =6;
                    Debug::Log("选中了场景中的物体$$$$$$$$ %s \n",(*ite)->GetGameObject()->name.c_str());
                    ImGui::TreePop();
                }
                if (node_open)
                {
                    showTransform((*ite)->GetGameObject()->transform);
                 
                }
                
                
//                if (ImGui::TreeNode((*ite)->GetGameObject()->name.c_str()))
//                {
//                    showTransform((*ite)->GetGameObject()->transform);
//                    ImGui::TreePop();
//                }
                
            }else
            {
                ImGuiTreeNodeFlags node_flags = ImGuiTreeNodeFlags_OpenOnArrow | ImGuiTreeNodeFlags_OpenOnDoubleClick;
                node_flags |= ImGuiTreeNodeFlags_Leaf | ImGuiTreeNodeFlags_NoTreePushOnOpen;
                int tempIndex = 9 ,node_clicked;
                ImGui::TreeNodeEx((void*)(intptr_t)tempIndex, node_flags,(*ite)->GetGameObject()->name.c_str());
                if (ImGui::IsItemClicked())
                {
                    Debug::Log("选中了场景中的物体 %s \n",(*ite)->GetGameObject()->name.c_str());
                    ImGui::TreePop();
                }
            }
            
        }
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
        
        
        if (ImGui::TreeNode("Scene"))
        {
            auto engine = Global<Context>().GetSubsystem<Engine>();
            auto scene = engine->currentScene;
            showTransform(scene->SceneRoot->transform);
            ImGui::TreePop();
        }
        
        
        ImGui::End();
    }
    

    
    void TmingEngine::Hierachy::End()
    {
    }

    
}
