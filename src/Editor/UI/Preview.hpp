
#ifndef Preview_hpp
#define Preview_hpp
#include <stdio.h>
#include "Core/SubSystem.h"
#include "Core/Context.h"
#include "Widget.h"
#include "im.h"

namespace TmingEngine
{
    class Preview :public Widget
    {
    public:
        
		Preview(Context *context)
        {
            m_title = "Preview";
        }
        ~Preview();
        
        void Begin();
        void Update();
        void End();
        
        int ImageId;
        
    };
}

#endif /* Preview_hpp */



