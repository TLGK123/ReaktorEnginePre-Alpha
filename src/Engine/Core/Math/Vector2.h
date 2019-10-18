//
////= INCLUDES ==================
//#include "../Core/EngineDefs.h"
//#include <string>
////=============================
//
//namespace TmingEngine
//{
//    class ENGINE_CLASS Vector2
//    {
//    public:
//        Vector2()
//        {
//            x = 0;
//            y = 0;
//        }
//
//        Vector2(const Vector2& vector)
//        {
//            this->x = vector.x;
//            this->y = vector.y;
//        }
//
//        Vector2(float x, float y)
//        {
//            this->x = x;
//            this->y = y;
//        }
//
//        ~Vector2() {}
//
//        //= ADDITION ===============================
//        Vector2 operator+(const Vector2& b)
//        {
//            return Vector2
//            (
//                this->x + b.x,
//                this->y + b.y
//            );
//        }
//
//        void operator+=(const Vector2& b)
//        {
//            this->x += b.x;
//            this->y += b.y;
//        }
//        //==========================================
//
//        //= MULTIPLICATION =======================================================================================
//        Vector2 operator*(const Vector2& b) const
//        {
//            return Vector2(x * b.x, y * b.y);
//        }
//
//        void operator*=(const Vector2& b)
//        {
//            x *= b.x;
//            y *= b.y;
//        }
//
//        Vector2 operator*(const float value) const
//        {
//            return Vector2(x * value, y * value);
//        }
//
//        void operator*=(const float value)
//        {
//            x *= value;
//            y *= value;
//        }
//        //=======================================================================================================
//
//
//        //= SUBTRACTION ===============================================================
//        Vector2 operator-(const Vector2& b) const { return Vector2(x - b.x, y - b.y); }
//        Vector2 operator-(const float value) { return Vector2(x - value, y - value); }
//
//        void operator-=(const Vector2& rhs)
//        {
//            x -= rhs.x;
//            y -= rhs.y;
//        }
//        //=============================================================================
//
//        //= DIVISION ========================================================================
//        Vector2 operator/(const Vector2& rhs) const { return Vector2(x / rhs.x, y / rhs.y); }
//        Vector2 operator/(const float rhs) { return Vector2(x / rhs, y / rhs); }
//
//        void operator/=(const Vector2& rhs)
//        {
//            x /= rhs.x;
//            y /= rhs.y;
//        }
//        //===================================================================================
//
//        bool operator==(const Vector2& b)
//        {
//            return x == b.x && y == b.y;
//        }
//
//        bool operator!=(const Vector2& b)
//        {
//            return x != b.x || y != b.y;
//        }
//
//        std::string ToString() const;
//
//        float x;
//        float y;
//        static const Vector2 Zero;
//        static const Vector2 One;
//    };
//}

#include "../EngineDefs.h"
#include <string>
namespace TmingEngine
{
    ENGINE_CLASS class Vector2
    {
     
    public:
        float x;
        float y;
        
        Vector2()
        {
            
        }
        
        Vector2(float x, float y)
        {
            this->x = x;
            this->y = y;
        }
        static const Vector2 Zero;
        static const Vector2 One;
        std::string ToString() const;
    };
}
