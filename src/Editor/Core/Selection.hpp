//
//  Selection.hpp
//  Editor
//
//  Created by lillteblue on 2019/5/26.
//

#ifndef Selection_hpp
#define Selection_hpp

#include <stdio.h>
#include "Core/Context.h"
#include "Scene/Components/Transform.h"

namespace TmingEngine
{
   static class Selecttion
    {
    public:
        static Context * activeContext;
        static Transform * activeTransform;
        static string GetActiveObjectName();
        
    };
}

#endif /* Selection_hpp */
