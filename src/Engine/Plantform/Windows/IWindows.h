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

// 注释掉就可以显示log  ,这个可以去掉黑色调试界面
//#pragma comment( linker, "/subsystem:\"windows\" /entry:\"mainCRTStartup\"" )

#ifndef IWindows_H
#define IWindows_H

#include <vector>

#include "Core/Context.h"
#include "Core/Subsystem.h"
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