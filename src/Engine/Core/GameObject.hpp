
#ifndef GameObject_hpp
#define GameObject_hpp
#include "EngineDefs.h"
#include "../Scene/Components/Transform.h"
#include "../Scene/Components/IComponent.h"

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
