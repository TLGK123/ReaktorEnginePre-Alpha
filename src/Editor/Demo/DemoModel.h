//
//  ModelTest.h
//  TmingEngine
//
//  Created by blue on 2018/9/2.
//

#ifndef ModelTest_h
#define ModelTest_h

#include "DemoTest.h"

class DemoModel :public DemoTest
{
public:
    DemoModel()
    {
    }
    
    ~DemoModel()
    {
    }
    
    void Render_SceneObject() override;
    
private:
    
};


#endif /* ModelTest_h */
