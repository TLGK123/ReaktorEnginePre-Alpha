//
//  Game.hpp
//  01_CaculateCode
//
//  Created by WangYiMing on 2019/5/15.
//

#ifndef Game_hpp
#define Game_hpp
#include <stdio.h>
#include "Core/SubSystem.h"
#include "Core/Context.h"
#include "Widget.h"
#include "im.h"

namespace TmingEngine
{
    class Game :public Widget
    {
    public:
        
        Game(Context *context)
        {
            m_title = "Game";
        }
        ~Game();
        
        void Begin();
        void Update();
        void End();
        
        int ImageId;
        
    };
}

#endif /* Game_hpp */



