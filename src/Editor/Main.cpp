/*
			This file is part of:
				TmingEngine
			https://github.com/xiaomingfun/TmingEngine

   Copyright 2018 - 2020 TmingEngine

   File creator: littleblue

   TmingEngine is open-source software and you can redistribute it and/or modify
   it under the terms of the License; besides, anyone who use this file/software must include this copyright announcement.

   Licensed under the Apache License, Version 2.0 (the "License");
   you may not use this file except in compliance with the License.
   You may obtain a copy of the License at

	   http://www.apache.org/licenses/LICENSE-2.0

   Unless required by applicable law or agreed to in writing, software
   distributed under the License is distributed on an "AS IS" BASIS,
   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
   See the License for the specific language governing permissions and
   limitations under the License.
*/
#ifdef WIN32
#include <WTypes.h> // Include this first on Win (bug #35683)
#endif

#include "Main.h"

#include <iostream>

using namespace std;
using namespace TmingEngine;
int main()
{
	Engine* engine;

	engine = new Engine(&Global<Context>());

	if (!engine->Initialize())
	{
		Debug::Log("TmingEngine----------Initialize----faild");
		return -1;
	}

	engine->SetEngineModeToEditor(true);
	engine->windows->InsertEditorWidget = SetEditorWidget;
	engine->InitializeWin();

	long frameNum = 0;
	while (!engine->ShouldClose())
	{
		frameNum++;
		engine->Update();
	}

	engine->Destory();
}

void SetEditorWidget()
{
	auto context = &Global<Context>();
	Engine* eg = context->GetSubsystem<Engine>();
	IWindows* win = eg->windows;
	win->RegisteWidget(new SceneView(context));
	//win->RegisteWidget(new DemoMenu(context));
	win->RegisteWidget(new Project(context));
	win->RegisteWidget(new Hierachy(context));
	win->RegisteWidget(new Inspector(context));
	win->RegisteWidget(new Game(context));
	win->RegisteWidget(new Profiler(context));
	win->RegisteWidget(new Console(context));
	win->RegisteWidget(new CodeEditor(context));
	win->RegisteWidget(new Preview(context));
	Debug::Log(" Editor 初始化窗口成功  ");
}