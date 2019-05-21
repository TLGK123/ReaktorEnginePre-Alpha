//
//  GameObject.hpp
//  01_CaculateCode
//
//  Created by WangYiMing on 2019/5/20.
//

#ifndef GameObject_hpp
#define GameObject_hpp
#include "EngineDefs.h"
#include "../Scene/Components/IComponent.h"
#include "../Scene/Components/Transform.h"
#include <string>
#include <stdio.h>
using namespace std;
namespace TmingEngine {
    
    class ENGINE_CLASS GameObject
    {
        
        public :
        GameObject();
        GameObject(string name);
     
        string name;
        Transform  * transform ;
        
        string GetGameObjectName();
        
        private :
        void Initializer();
        
         
    };
    
}


#endif /* GameObject_hpp */
