//
//  Profiler.cpp
//  01_CaculateCode
//
//  Created by WangYiMing on 2019/5/15.
//

#include "Profiler.hpp"

TmingEngine::Profiler::~Profiler()
{
}

void TmingEngine::Profiler::Begin()
{
}

void TmingEngine::Profiler::Update()
{
    bool p_open = true;
    ImGui::SetNextWindowSize(ImVec2(350, 180), ImGuiCond_FirstUseEver);
    if (!ImGui::Begin("Profiler", &p_open))
    {
        ImGui::End();
        return;
    }
    
    
    {
        static bool animate = true;
        ImGui::Checkbox("Animate", &animate);
        
        static float values[90] = { 0 };
        static int values_offset = 0;
        static double refresh_time = 0.0;
        if (!animate || refresh_time == 0.0)
            refresh_time = ImGui::GetTime();
        while (refresh_time < ImGui::GetTime()) // Create dummy data at fixed 60 hz rate for the demo
        {
            static float phase = 0.0f;
            values[values_offset] = cosf(phase);
            values_offset = (values_offset+1) % IM_ARRAYSIZE(values);
            phase += 0.10f*values_offset;
            refresh_time += 1.0f/5.0f;
        }
        ImGui::PlotLines("Lines", values, IM_ARRAYSIZE(values), values_offset, "avg 0.0", -1.0f, 1.0f, ImVec2(0,160));

    }
    
    ImGui::End();
}

void TmingEngine::Profiler::End()
{
}
