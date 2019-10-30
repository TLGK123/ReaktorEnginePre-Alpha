
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
        
        unsigned int ImageId;
		unsigned int texture1;
		void PreviewTexture(string path);
        
    };
}

#endif /* Preview_hpp */



