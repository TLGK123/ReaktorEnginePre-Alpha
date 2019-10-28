//
//  Inspector.hpp
//  01_CaculateCode
//
//  Created by blue on 2019/5/15.
//
#pragma once

#ifndef Inspector_hpp
#define Inspector_hpp
#include <stdio.h>
#include "Core/SubSystem.h"
#include "Core/Context.h"
#include "Widget.h"
#include "im.h"
#include "Selection.hpp"

namespace TmingEngine
{
    class Inspector :public Widget
    {
    public:
        
        Inspector(Context *context)
        {
            m_title = "Inspector";
        }
        ~Inspector();
        
        void Begin();
        void Update();
        void End();
        
        int ImageId;
        
    };
}

#endif /* Inspector_hpp */
