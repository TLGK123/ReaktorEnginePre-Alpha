//The MIT License
//
//Copyright(c) 2016 - 2019 littleblue
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
//
//  Created by lillteblue on 2019/5/15.
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
