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
 
	while (!screen->ScreenShouldClose())
	{
		screen->Update();
		engine->Tick();
	}

	screen->ShutDown();
	engine->Shutdown();
}
