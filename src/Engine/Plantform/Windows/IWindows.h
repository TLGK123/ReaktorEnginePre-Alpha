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

// 注释掉就可以显示log  ,这个可以去掉黑色调试界面
//#pragma comment( linker, "/subsystem:\"windows\" /entry:\"mainCRTStartup\"" )

#ifndef TmingEngine_Engine_Plantform_Windows_IWindows_H_
#define TmingEngine_Engine_Plantform_Windows_IWindows_H_

#include <vector>

#include "Core/Context.h"
#include "Core/SubSystem.h"
#include "Widget.h"

using namespace std;

namespace TmingEngine
{
	class ENGINE_CLASS IWindows : public Subsystem
	{
	public:

		IWindows(Context* context) : Subsystem(context)
		{
		}
		virtual void WinRender() = 0;
		virtual void WinClose() = 0;
		virtual bool WinShouldClose() = 0;
		virtual void SetViewPoint(int startX, int startY, int width, int height) = 0;
		vector<Widget*> m_widgets;

		void (*InsertEditorWidget)() = nullptr;

		void RegisteWidget(Widget* widget)
		{
			m_widgets.push_back(widget);
		}

		bool isEditorWindows = false;

		template <class T>
		T* GetSubWidget()
		{
			for (const auto& subwidget : m_widgets)
			{
				if (typeid(T) == typeid(*subwidget))
					return static_cast<T*>(subwidget);
			}
			return nullptr;
		}

		void DrawScreenWidgets()
		{
			for (auto& widget : m_widgets)
			{
				widget->Update();
			}
		}
	};
}

#endif