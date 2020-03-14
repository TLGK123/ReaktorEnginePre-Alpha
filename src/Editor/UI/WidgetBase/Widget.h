#pragma once
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

#include<string>
#include"Core/SmartPtr.h"
#include "ImGUI/imgui.h"

namespace TmingEngine
{
	class Context;

	class Widget :public RefCount
	{
	public:
		virtual ~Widget() {}
		virtual void Initialize(TmingEngine::Context* context);
		virtual void Begin();
		virtual void Update();
		virtual void End();
		bool GetIsWindow() { return m_isWindow; }
		void Show() { p_open = true; };
		void Hide() { p_open = false; };

	protected:
		TmingEngine::Context* m_context = nullptr;
		bool p_open = false;
		bool m_isWindow = true;
		std::string m_title;
		int m_windowFlags = 0;

	};
}
