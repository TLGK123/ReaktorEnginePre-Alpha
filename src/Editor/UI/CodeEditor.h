#pragma once
#ifndef TextEditor_h
#define TextEditor_h

#include "Core/SubSystem.h"
#include "Core/Context.h"
#include "Widget.h"
#include "im.h"
#include "Core/Log/Log.h"


namespace TmingEngine
{
	class CodeEditor : public Widget
	{
	public:
		//ImGuiTextBuffer     Buf;
		//ImGuiTextFilter     Filter;
		//ImVector<int>       LineOffsets;        // Index to lines offset
		//bool                ScrollToBottom;

		CodeEditor(Context* context)
		{
		}
		~CodeEditor();

		void Begin();
		void Update();
		void End();

		void Clear();
		void AddLog(const char* fmt, ...);
		void Draw(const char* title, bool* p_open);
		void Draw2(const char* title, bool* p_open);
	};
}
#endif
