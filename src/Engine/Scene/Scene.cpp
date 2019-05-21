//
//  Scene.cpp
//  TmingEngine
//
//  Created by WangYiMing on 2019/5/21.
//

#include "Scene.hpp"

namespace TmingEngine {

    Scene::Scene()
    {

        SceneRoot = new GameObject("SceneRoot");
        auto camera = new GameObject("Main Camera");
        camera->transform->SetParent(SceneRoot->transform);

        auto go = new GameObject("Cube");
        go->transform->SetParent(SceneRoot->transform);
        ;
    }
    
    
    
}
