//
//  Profiler.hpp
//  Created by lillteblue on 2019/5/15.
//

#ifndef Profiler_hpp
#define Profiler_hpp

#include <stdio.h>
#include "Core/SubSystem.h"
#include "Core/Context.h"
#include "Widget.h"
#include "im.h"

namespace TmingEngine
{
    class Profiler :public Widget
    {
    public:
        
        Profiler(Context *context)
        {
            m_title = "Profiler";
        }
        ~Profiler();
        
        void Begin();
        void Update();
        void End();
        
        int ImageId;
    };
}


#endif /* Profiler_hpp */
