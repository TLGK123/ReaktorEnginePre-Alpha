/*
Copyright(c) 2016-2019 Panos Karabelas

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and / or sell
copies of the Software, and to permit persons to whom the Software is furnished
to do so, subject to the following conditions :

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS
FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.IN NO EVENT SHALL THE AUTHORS OR
COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER
IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/

#pragma once
#include "../EngineDefs.h"
#include <string>
#include <math.h>

namespace TmingEngine {
    ENGINE_CLASS class Vector3
    {
        
    public:
        float x;
        float y;
        float z;
        
        Vector3()
        {
            x=0;
            y=0;
            z=0;
        }
        
        Vector3(float x, float y,float z)
        {
            this->x = x;
            this->y = y;
            this->z = z;
        }
                static const Vector3 Zero;
                static const Vector3 Left;
                static const Vector3 Right;
                static const Vector3 Up;
                static const Vector3 Down;
                static const Vector3 Forward;
                static const Vector3 Back;
                static const Vector3 One;
                static const Vector3 Infinity;
                static const Vector3 InfinityNeg;
        std::string ToString() const;
        
        bool operator==(const Vector3 & other) const
        {
            return x == other.x && y == other.y && z == other.z;
        }
        
        Vector3 operator+(const Vector3 & other)const
        {
            return Vector3(x+other.x, y + other.y,z + other.z);
        }
        
        void operator+=(const Vector3 & other)
        {
            x += other.x;
            y += other.y;
            z += other.z;
        }
        
        Vector3 operator-(const Vector3 & other)const
        {
            return Vector3(x - other.x, y - other.y,z - other.z);
        }
        
        void operator-=(const Vector3 & other)
        {
            x -= other.x;
            y -= other.y;
            z -= other.z;
        }
        
        static Vector3 Cross(const Vector3& v1, const Vector3& v2)
        {
            float x = v1.y * v2.z - v2.y * v1.z;
            float y = -(v1.x * v2.z - v2.x * v1.z);
            float z = v1.x * v2.y - v2.x * v1.y;
            return Vector3(x, y, z);
        }
        
        static float Dot(const Vector3& v1, const Vector3& v2)
        {

            return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z ;
        }
        
        static Vector3 Normalize(const Vector3& v )
        {
            float len = sqrt(v.x * v.x + v.y * v.y + v.z * v.z);
            float v1 = abs( v.x / len)<=0.00001 ? 0 :v.x/len;
            float v2 = abs( v.y / len)<=0.00001 ? 0 :v.y/len;
            float v3 = abs( v.z / len)<=0.00001 ? 0 :v.z/len;
            
            return Vector3(v1 , v2 ,v3);
        }
        
        Vector3 operator*(const float other)const
        {
            return Vector3(x * other, y * other ,z * other);
        }
        
        
    };
}
