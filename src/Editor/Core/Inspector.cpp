//
//  Inspector.cpp
//  01_CaculateCode
//
//  Created by WangYiMing on 2019/5/15.
//

#include "Inspector.hpp"

TmingEngine::Inspector::~Inspector()
{
}

void TmingEngine::Inspector::Begin()
{
}

void TmingEngine::Inspector::Update()
{
    bool p_open = true;
    ImGui::SetNextWindowSize(ImVec2(350, 560), ImGuiCond_FirstUseEver);
    if (!ImGui::Begin("Inspector", &p_open))
    {
        ImGui::End();
        return;
    }
    
    
    ImGui::Text("this  is Detial Panel ");
    
    ImGui::End();
}

void TmingEngine::Inspector::End()
{
}

