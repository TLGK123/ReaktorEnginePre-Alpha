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
                ImGui::Text((*ite)->GetGameObjectName().c_str());
                
            }else
            {
                if (ImGui::TreeNode((*ite)->GetGameObjectName().c_str()))
                {
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
        
        
        if (ImGui::TreeNode("Basic trees"))
        {
            auto engine = Global<Context>().GetSubsystem<Engine>();
            auto scene = engine->currentScene;
            showTransform(scene->SceneRoot->transform);
            ImGui::TreePop();
        }
        
        
        ImGui::Text("this is project view");
        
        ImGui::End();
    }
    

    
    void TmingEngine::Hierachy::End()
    {
    }

    
}
