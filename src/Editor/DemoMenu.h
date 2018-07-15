#ifndef DemoMenu_h
#define DemoMenu_h

#include "Core/SubSystem.h"
#include "Core/Context.h"
#include "imgui.h"
#include "imgui_impl_glfw_gl3.h"
#include "Log/Log.h"
#include "UI/Widgets/Widget.h"

namespace TmingEngine
{

	class DemoMenu :public Widget
	{
	public:

		DemoMenu(Context *context)
		{
			m_title = "ViewPoint";
		}
		int testIndex = 0;
		int testCount = 3;

		int testSelection;

		void Begin();
		void Update();
		void End();
	};
}

#endif