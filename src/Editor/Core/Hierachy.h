#pragma once
#include "Core/SubSystem.h"
#include "Core/Context.h"
#include "Widget.h"
#include "im.h"

namespace TmingEngine
{
	class Hierachy :public Widget
	{
	public:

		Hierachy(Context *context)
		{
			m_title = "Hierachy";
		}
		~Hierachy();

		void Begin();
		void Update();
		void End();

		int ImageId;
		
	};
}
