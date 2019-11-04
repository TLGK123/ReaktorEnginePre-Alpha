//The MIT License
//
//Copyright(c) 2018 - 2019 littleblue
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


#include "Scene.hpp"

namespace TmingEngine {

    Scene::Scene()
    {
        name = "Unitled";
        SceneRoot = new GameObject("SceneRoot");
        auto camera = new GameObject("Main Camera");
        camera->transform->SetParent(SceneRoot->transform);
        camera->transform->SetPositionLocal(Vector3(0.0f, 0.0f, 5.0f));

//        auto go = new GameObject("Cube");
//        go->transform->SetParent(SceneRoot->transform);
//        
//        auto go1 = new GameObject("Cube1");
//        go1->transform->SetParent(SceneRoot->transform);
//        
//        auto go2 = new GameObject("Cube2");
//        go2->transform->SetParent(SceneRoot->transform);
//        
//        auto go3 = new GameObject("Cube3");
//        go3->transform->SetParent(go2->transform);
//        
//        auto go4 = new GameObject("Cube4");
//        go4->transform->SetParent(go2->transform);
//        ;
    }
    
    void Scene::Update()
    {
        RendeObject();
    }
    
    void Scene::RendeObject()
    {
        
    }
}
