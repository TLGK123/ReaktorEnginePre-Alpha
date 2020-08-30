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

#ifndef TmingEngine_Engine_Plantform_Windows_Widget_H_
#define TmingEngine_Engine_Plantform_Windows_Widget_H_

#include<string>
#include "Core/SmartPtr.h"
#include "ImGui/imgui.h"

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

#endif