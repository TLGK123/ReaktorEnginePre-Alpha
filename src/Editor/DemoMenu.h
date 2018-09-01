#ifndef DemoMenu_h
#define DemoMenu_h
#include "Core/SubSystem.h"
#include "Core/Context.h"
#include "UI/Widgets/Widget.h"
#include "Log/Log.h"
#include "im.h"


namespace TmingEngine
{
	class DemoMenu :public Widget
	{
	public:

		DemoMenu(Context *context) 
		{
			m_title = "ViewPoint";
			m_context = context;
		}
		int testIndex = 0;
		int testCount = 2;

		int testSelection;

		void Begin();
		void Update();
		void End();
	};
}

#endif
