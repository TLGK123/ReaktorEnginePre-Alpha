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
	Screen *screen;
	Engine *engine;

	screen = new Screen(&Global<Context>());
    
    engine = new Engine(&Global<Context>());
    if (!engine->Initialize())
    {
        return -1;
    };
    
	Debug::Log("hello world");

	while (!screen->ScreenShouldClose())
	{
		screen->Update();
		engine->Tick();
	}

	screen->ShutDown();
	engine->Shutdown();
}
