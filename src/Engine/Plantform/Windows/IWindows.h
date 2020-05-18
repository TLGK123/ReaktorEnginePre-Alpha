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

#ifndef IWindows_H
#define IWindows_H

#include "Core/Context.h"
#include "Core/Subsystem.h"
#include <vector>
using namespace std;

namespace TmingEngine
{
	class Widget;
	class ENGINE_CLASS IWindows : public Subsystem
	{
	public:
		IWindows(Context* context);
		virtual void WinInitialize() = 0;   //´¿Ðéº¯Êý =0 ±íÊ¾
		virtual void WinRender() = 0;
		virtual void WinClose() = 0;
		virtual bool WinShouldClose() = 0;

		vector<Widget*> m_widgets;
		void RegisteWidget(Widget* widget)
		{
			m_widgets.push_back(widget);
		}

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
			//for (auto& widget : m_widgets)
			//{
			//	widget->Update();
			//}
		}
	};

}



#endif