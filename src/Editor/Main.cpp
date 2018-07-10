//
//  Main.c
//  Editor
//  Created by blue on 2018/6/16.
#include "Main.h"
#include <iostream>
using namespace std;
using namespace TmingEngine;

int main()
{
	Screen *screen = new Screen();
	screen->Initialize();

	Engine *engine = new Engine(new Context());
	engine->Initialize();

	while (!screen->ScreenShouldClose())
	{
		screen->Update();
		engine->Tick();
	}
	screen->ShutDown();
	engine->Shutdown();
}

