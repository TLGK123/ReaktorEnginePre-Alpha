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
    
    auto selectActive =Selecttion::activeTransform;
    if(selectActive != NULL)
    {
        ImGui::Text(Selecttion::GetActiveObjectName().c_str());
        static Math::Vector3 pos = selectActive->GetPositionLocal();
        ImGui::InputFloat("X",& pos.x , 1.0f);
        ImGui::InputFloat("Y",& pos.y , 1.0f);
        ImGui::InputFloat("Z",& pos.z , 1.0f);
        selectActive->SetPositionLocal(pos);
        
        
    }

    ImGui::End();
}

void TmingEngine::Inspector::End()
{
}

