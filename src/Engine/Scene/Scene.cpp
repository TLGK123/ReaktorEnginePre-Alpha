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
        name = "Unitled";
        SceneRoot = new GameObject("SceneRoot");
        auto camera = new GameObject("Main Camera");
        camera->transform->SetParent(SceneRoot->transform);

        auto go = new GameObject("Cube");
        go->transform->SetParent(SceneRoot->transform);
        
        auto go1 = new GameObject("Cube1");
        go1->transform->SetParent(SceneRoot->transform);
        
        auto go2 = new GameObject("Cube2");
        go2->transform->SetParent(SceneRoot->transform);
        
        auto go3 = new GameObject("Cube3");
        go3->transform->SetParent(go2->transform);
        
        auto go4 = new GameObject("Cube4");
        go4->transform->SetParent(go2->transform);
        ;
    }
    
    void Scene::Update()
    {
        RendeObject();
    }
    
    void Scene::RendeObject()
    {
        
    }
}
