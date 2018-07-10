//
//  Main.c
//  Editor
//
//  Created by blue on 2018/6/16.
#include "Main.h"
#include <iostream>
using namespace std;

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

}
