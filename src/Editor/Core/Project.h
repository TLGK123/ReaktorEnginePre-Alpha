#pragma once
#include "Core/SubSystem.h"
#include "Core/Context.h"
#include "Widget.h"
#include "im.h"

namespace TmingEngine
{
	class Project :public Widget
	{
	public:

		Project(Context *context)
		{
			m_title = "Project";
		}
		~Project();

		void Begin();
		void Update();
		void End();

		int ImageId;
		
	};
}
