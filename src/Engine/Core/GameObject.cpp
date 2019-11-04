//
//  GameObject.cpp
//  01_CaculateCode
//
//  Created by lillteblue = on 2019/5/20.
//

//= INCLUDES ==========
#include "GameObject.hpp"
#include "Context.h"
//====================

 namespace TmingEngine
{
    GameObject::GameObject()
    {
        Initializer();
    }
    
    GameObject::GameObject(string ObjectName)
    {
        name = ObjectName;
        Initializer();
    }
    
    void GameObject::Initializer()
    {
        auto context = & Global<Context>();
        transform = new Transform( context,this,nullptr);
    }
    
    string GameObject::GetGameObjectName()
    { 
        return name;
    }

    
}

