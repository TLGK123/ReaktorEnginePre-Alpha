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


		CodeEditor(Context* context)
		{
		}
		~CodeEditor();

		void Begin();
		void Update();
		void End();

	};
}
#endif
