#include "Vector2.h"
#include <stdio.h>

using namespace std;

namespace TmingEngine
{
    const Vector2 Vector2::Zero(0.0f, 0.0f);
    const Vector2 Vector2::One(1.0f, 1.0f);

    string Vector2::ToString() const
    {
        char tempBuffer[200];
        sprintf(tempBuffer, "X:%f, Y:%f", x, y);
        return string(tempBuffer);
    }
}
