//
//  Main.c
//  Editor
//  Created by blue on 2018/6/16.
#include "Main.h"
#include "Screen.h"
#include <iostream>
using namespace std;
using namespace TmingEngine;

int main()
{

	Engine *engine;
    Screen *screen;

    engine = new Engine(&Global<Context>());
    if (!engine->Initialize())
    {
        return -1;
    };
    
    screen = new Screen(&Global<Context>());
    if (!screen->Initialize())
    {
        return -1;
    };
    Debug::Log("hello world");
    

 while (!screen->ScreenShouldClose())
	{
        engine->Tick();
        screen->Update();
	}

	screen->ShutDown();
	engine->Shutdown();
}
