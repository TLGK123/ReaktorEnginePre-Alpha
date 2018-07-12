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
	//SmartPtr<Context> context =
	Screen *screen;
	Engine *engine;

	engine = new Engine(&Global<Context>());
	if (!engine->Initialize())
	{
		Debug::Log("ÒýÇæ³õÊ¼»¯Ê§°Ü");
		return -1;
	};
	screen = new Screen(&Global<Context>());

	while (!screen->ScreenShouldClose())
	{
		screen->Update();
		engine->Tick();
	}

	screen->ShutDown();
	engine->Shutdown();
}