//
//  Scene.hpp
//  TmingEngine
//
//  Created by WangYiMing on 2019/5/21.
//

#ifndef Scene_hpp
#define Scene_hpp

#include <string>
#include <stdio.h>
#include "../../Core/GameObject.hpp"
#include "../Scene/Components/Transform.h"

using namespace std;
namespace TmingEngine {
    class Scene
    {
    public:
        
        int buildIndex;
        bool isDirty;
        bool isLoaded;
        string path;
        string name;
        
        GameObject * SceneRoot;
        bool IsValid();
        Scene();
        
        void Update();
    private:
        
        void RendeObject();
    };
 
}


#endif /* Scene_hpp */
