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

	EngineInit();
	while (!screen->ScreenShouldClose())
	{
		screen->Update();
	}
	screen->ShutDown();
}

void EngineInit()
{
	Engine *engine = new Engine(new Context());
}