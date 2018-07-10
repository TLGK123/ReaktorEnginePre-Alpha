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
	Engine *engine = new Engine(new Context());
	if (!engine->Initialize())
	{
		Debug::Log("ÒýÇæ³õÊ¼»¯Ê§°Ü");
		return -1;
	};
	auto engineContext = engine->GetContext();
	screen->Initialize(engineContext);
   
	while (!screen->ScreenShouldClose())
	{
		screen->Update();
		engine->Tick();
	}

	screen->ShutDown();
	engine->Shutdown();
}