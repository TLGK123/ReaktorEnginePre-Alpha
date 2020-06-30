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

#include "Log.h"
using namespace std;
namespace TmingEngine
{
	void Debug::Log(const char * message, ...)
	{
        std::cout << message << std::endl;
		//printf(message);
		//Global<Context>().GetSubsystem<Console>()->AddLog(message);
	}
    
    void Debug::Log(string msg)
    {
        std::cout << msg << std::endl;
       // printf(msg.c_str());
        //Global<Context>().GetSubsystem<Console>()->AddLog(message);
    }
    
    void Debug::Log(glm::mat4 m)
    {
        char tempBuffer[200];
        sprintf(tempBuffer, "\n%10f, %10f, %10f, %10f,\n%10f, %10f, %10f, %10f,\n%10f, %10f, %10f, %10f,\n%10f, %10f, %10f, %10f\n", m[0][0], m[0][1], m[0][2], m[0][3], m[1][0], m[1][1], m[1][2], m[1][3], m[2][0], m[2][1], m[2][2], m[2][3], m[3][0], m[3][1], m[3][2], m[3][3]);
        printf(string(tempBuffer).c_str());
    }
}
