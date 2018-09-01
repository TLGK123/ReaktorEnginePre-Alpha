#pragma once
#include "Core/SubSystem.h"
#include "Core/Context.h"
#include "Widget.h"
#include "im.h"

namespace TmingEngine
{
	class ViewPoint :public Widget
	{
	public:

		ViewPoint(Context *context)
		{
			m_title = "ViewPoint";
		}
		~ViewPoint();

		void Begin();
		void Update();
		void End();

		int ImageId;
		void SetTexture(int Id);	
	};
}
