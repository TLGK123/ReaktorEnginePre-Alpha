#pragma once
#ifndef CodeEditor_h
#define CodeEditor_h

#include "Core/SubSystem.h"
#include "Core/Context.h"
#include "Plantform/Windows/Widget.h"
#include "im.h"
#include "Core/Log/Log.h"
#include "TextEditor/TextEditor.h"

namespace TmingEngine
{
	class CodeEditor : public Widget
	{
	public:

		CodeEditor(Context* context)
		{
		}
		~CodeEditor();

		string fileToEdit = "ImGuiColorTextEdit/TextEditor.cpp";
		TextEditor editor;
		void Begin();
		void Update();
		void End();

	};
}
#endif
