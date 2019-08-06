#include "Log.h"
using namespace std;
namespace TmingEngine
{
	void Debug::Log(const char * message, ...)
	{
		printf(message);
		//Global<Context>().GetSubsystem<Console>()->AddLog(message);
	}
    
    void Debug::Log(string msg)
    {
        printf(msg.c_str());
        //Global<Context>().GetSubsystem<Console>()->AddLog(message);
    }
    
    void Debug::Log(glm::mat4 m)
    {
        char tempBuffer[200];
        sprintf(tempBuffer, "\n%10f, %10f, %10f, %10f,\n%10f, %10f, %10f, %10f,\n%10f, %10f, %10f, %10f,\n%10f, %10f, %10f, %10f\n", m[0][0], m[0][1], m[0][2], m[0][3], m[1][0], m[1][1], m[1][2], m[1][3], m[2][0], m[2][1], m[2][2], m[2][3], m[3][0], m[3][1], m[3][2], m[3][3]);
        printf(string(tempBuffer).c_str());
    }
}
