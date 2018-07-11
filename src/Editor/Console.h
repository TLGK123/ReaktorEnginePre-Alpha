#pragma once
#include "Core/SubSystem.h"
#include "Core/Context.h"
#include "imgui.h"
#include "imgui_impl_glfw_gl3.h"
#include "Log/Log.h"

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
	};
}
