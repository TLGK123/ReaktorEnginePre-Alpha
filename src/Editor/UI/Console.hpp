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

#ifndef TmingEngine_Editor_UI_Console_hpp
#define TmingEngine_Editor_UI_Console_hpp

#include "Core/Log.h"
#include "Core/Engine.h"
#include "Core/SubSystem.h"
#include "Core/Context.h"
#include "Plantform/Windows/Widget.h"
#include "Game.hpp"

extern "C"
{
	//#include "Scheme/include/scheme.h"
}

extern "C"
{
#include "lua.h"
#include "lauxlib.h"
#include "lualib.h"
}

#include <mono/jit/jit.h>
#include <mono/metadata/assembly.h>
#include <mono/metadata/class.h>
#include <mono/metadata/debug-helpers.h>
#include <mono/metadata/mono-config.h>
#include <mono/metadata/mono-debug.h>

#include <angelscript.h>
#include <scriptstdstring/scriptstdstring.h>
#include <scriptbuilder/scriptbuilder.h>

#include "ScriptEngine/scheme.hpp"

namespace TmingEngine
{
	void ConfigureEngine(asIScriptEngine* engine);
	int  CompileScript(asIScriptEngine* engine);
	void PrintString(string& str);
	void PrintString_Generic(asIScriptGeneric* gen);
	void timeGetTime_Generic(asIScriptGeneric* gen);
	void LineCallback(asIScriptContext* ctx, unsigned long* timeOut);

	class Console : public Widget
	{
	public:
		ImGuiTextBuffer     Buf;
		ImGuiTextFilter     Filter;
		ImVector<int>       LineOffsets;        // Index to lines offset
		bool                ScrollToBottom;

		Console(Context* context)
		{
		}
		~Console();

		void Begin();
		void Update();
		void End();

		void Clear();
		void AddLog(const char* fmt, ...);
		void Draw(const char* title, bool* p_open);
		//void Draw2(const char* title, bool* p_open);
		void TestLua();
		int TestAngleScript();
		void TestScheme();

		void TestMono();
	};
} // namespace TmingEngine
#endif // TmingEngine_Editor_UI_Console_hpp
