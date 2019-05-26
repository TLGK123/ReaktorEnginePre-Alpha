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
//                ImGuiTreeNodeFlags node_flags = ImGuiTreeNodeFlags_OpenOnArrow | ImGuiTreeNodeFlags_OpenOnDoubleClick;
//                if (ImGui::TreeNodeEx((void*)(intptr_t)9, node_flags, (*ite)->GetGameObject()->name.c_str()))
//                {
//                    if (ImGui::IsItemClicked())
//                    {
//                        Debug::Log("选中---父级对象 %s \n",(*ite)->GetGameObject()->name.c_str());
//                    }
//                    showTransform((*ite)->GetGameObject()->transform);
//                    ImGui::TreePop();
//                }
                
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
    
    void TmingEngine::Hierachy::Update()
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
        if (ImGui::TreeNode(scene->name.c_str()))
        {
            showTransform(scene->SceneRoot->transform);
            ImGui::TreePop();
        }
        
        
        ImGui::End();
    }
    

    
    void TmingEngine::Hierachy::End()
    {
    }

    
}
