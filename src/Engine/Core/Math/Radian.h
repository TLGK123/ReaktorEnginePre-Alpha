#pragma once
#include "../Core/EngineDefs.h"
#include <string>

namespace TmingEngine
{
    static const float Pi = 3.1415926;
    ENGINE_CLASS class Radian
    {
    
    private:
        float value;
    public:
        float x;
        
        Radian()
        {
            
        }
        
        Radian(float x)
        {
            this->x = x;
            value = x / 360.0f * 2 * Pi;
        }
       
        float GetRadian()
        {
            return value;
        }
        
        float GetAngle()
        {
            return x;
        }
        
//        static void operator*() const
//        {
//            
//        }

        std::string ToString() const;
    };
}
