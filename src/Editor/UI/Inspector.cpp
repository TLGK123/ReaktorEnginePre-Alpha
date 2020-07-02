/*
            This file is part of: 
                TmingEngine
            https://github.com/xiaomingfun/TmingEngine

   Copyright 2016 - 2020 TmingEngine(NoahGameFrame)

   File creator: littleblue
   
   TmingEngine is open-source software and you can redistribute it and/or modify
   it under the terms of the License; besides, anyone who use this file/software must include this copyright announcement.

   Licensed under the Apache License, Version 2.0 (the "License");
   you may not use this file except in compliance with the License.
   You may obtain a copy of the License at

       http://www.apache.org/licenses/LICENSE-2.0

   Unless required by applicable law or agreed to in writing, software
   distributed under the License is distributed on an "AS IS" BASIS,
   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
   See the License for the specific language governing permissions and
   limitations under the License.
*/

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
        Vector3 pos = selectActive->GetPositionLocal();
        
        ImGui::InputFloat("X",& pos.x , 1.0f);
        ImGui::InputFloat("Y",& pos.y , 1.0f);
        ImGui::InputFloat("Z",& pos.z , 1.0f);
        
        Vector3 v =  Vector3(pos.x,pos.y,pos.z);
        selectActive->SetPositionLocal(v);
        
        
    }

    ImGui::End();
}

void TmingEngine::Inspector::End()
{
}

