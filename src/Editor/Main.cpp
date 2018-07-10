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
	screen->Init();

	Engine *engine = new Engine(new Context());
	engine->Initialize();

	while (!screen->ScreenShouldClose())
	{
		screen->Update();
		engine->Update();
	}
	screen->ShutDown();
	engine->Shutdown();
}

