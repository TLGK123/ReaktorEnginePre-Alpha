//The MIT License
//
//Copyright(c) 2016 - 2020 littleblue
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

//  Main.cpp
//  Created by lillteblue on 2018/6/16.

#include "Main.h"
#include "Screen.h"
#include <iostream>
using namespace std;
using namespace TmingEngine;


int main()
{
	Engine *engine;

    engine = new Engine(&Global<Context>());
    if (!engine->Initialize())
    {
        Debug::Log("TmingEngine----------Initialize----faild");
        return -1;
    }
    else
    {
        Debug::Log("TmingEngine----------Initialize-----");
        Global<Context>().RegisterSubsystem(new ScreenSystem());
    };

    long frameNum = 0;
	while (!engine->ShouldClose())
	{
        frameNum++;
        engine->Update();
	}

	engine->Destory();
}
