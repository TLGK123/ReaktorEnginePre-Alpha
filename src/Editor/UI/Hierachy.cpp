//The MIT License
//
//Copyright(c) 2016 - 2020 littleblue
//
//Permission is hereby granted, free of charge, to any person obtaining a copy
//of this softwareand associated documentation files(the "Software"), to deal
//in the Software without restriction, including without limitation the rights
//to use, copy, modify, merge, publish, distribute, sublicense, and / or sell
//copies of the Software, and to permit persons to whom the Software is furnished
//to do so, subject to the following conditions :
//
//The above copyright noticeand this permission notice shall be included in
//all copies or substantial portions of the Software.
//
//THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
//IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS
//FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.IN NO EVENT SHALL THE AUTHORS OR
//COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER
//IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
//CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.


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
        if (ImGui::TreeNode("test"))
        {
            //showTransform(scene->SceneRoot->transform);
            ImGui::TreePop();
        }
        
        
        ImGui::End();
    }
    

    
    void TmingEngine::Hierachy::End()
    {
    }

    
}
