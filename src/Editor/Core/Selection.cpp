//
//  Selection.cpp
//  Editor
//
//  Created by lillteblue on 2019/5/26.
//

#include "Selection.hpp"

namespace TmingEngine {
    
    Context * Selecttion:: activeContext = NULL;
    Transform * Selecttion:: activeTransform = NULL;
    
    string Selecttion::GetActiveObjectName()
    {
        if(activeTransform!=NULL)
        {
              return activeTransform->GetGameObject()->GetGameObjectName();
        }else
        {
              return "Unselect any Object";
        }
      
    }
}
