/*
//Copyright(c) 2016 - 2020 littleblue

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and / or sell
copies of the Software, and to permit persons to whom the Software is furnished
to do so, subject to the following conditions :

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS
FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.IN NO EVENT SHALL THE AUTHORS OR
COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER
IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/

#pragma once
#include "Context.h"
#define ENGINE_VERSION "v0.0.1"
#define TmengineLib
#include "../Scene/Scene.hpp"
#include "Plantform/Windows/IWindows.h"

namespace TmingEngine
{

	class Timer;

	class ENGINE_CLASS Engine : public Subsystem
	{
	public:
		
		Engine(Context* context);
		
		bool Initialize() override;

		void InitializeWin();

		void Update();

		void Destory();

		bool ShouldClose();


		Context* GetContext() { return m_context; }

        Scene * currentScene;

		IWindows* windows;
	private:

		Timer* m_timer;
	};
}
