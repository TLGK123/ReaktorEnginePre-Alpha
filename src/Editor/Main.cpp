//The MIT License
//
//Copyright(c) 2016 - 2019 littleblue
//
//Permission is hereby granted, free of charge, to any person obtaining a copy
//of this softwareand associated documentation files(the "Software"), to deal
//in the Software without restriction, including without limitation the rights
//to use, copy, modify, merge, publish, distribute, sublicense, and / or sell
//copies of the Software, and to permit persons to whom the Software is furnished
//to do so, subject to the following conditions :
//
//The above copyright noticeand this permission notice shall be included in
//all copies or substantial portions of the Software.
//
//THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
//IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS
//FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.IN NO EVENT SHALL THE AUTHORS OR
//COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER
//IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
//CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

//  Main.c
//  Editor
//  Created by lillteblue on 2018/6/16.

#include "Main.h"
#include "Editor.h"
#include <iostream>
using namespace std;
using namespace TmingEngine;

int main()
{

	Engine *engine;
    Editor *screen;

	MonoHelp::Start();
    engine = new Engine(&Global<Context>());
    if (!engine->Initialize())
    {
        return -1;
    };
    
    screen = new Editor(&Global<Context>());
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
	MonoHelp::End();
	screen->ShutDown();
	engine->Shutdown();
}
