#pragma once
#ifndef console_h
#define console_h

#include "Core/SubSystem.h"
#include "Core/Context.h"
#include "im.h"


namespace TmingEngine
{
	class Console :public Subsystem
	{
	public:
		ImGuiTextBuffer     Buf;
		ImGuiTextFilter     Filter;
		ImVector<int>       LineOffsets;        // Index to lines offset
		bool                ScrollToBottom;

		Console(Context *context) : Subsystem(context)
		{
		}
		~Console();

		void Clear();
		void AddLog(const char* fmt, ...);
		void Draw(const char* title, bool* p_open);
		void Draw2(const char* title, bool* p_open);
	};
}
#endif
