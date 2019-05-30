#pragma once
#include "Core/SubSystem.h"
#include "Core/Context.h"
#include "Widget.h"
#include "im.h"
#include "../../../src/Engine/Core/Engine.h"
#include "../../../src/Engine/Scene/Components/Transform.h"
#include "../../../src/Engine/Log/Log.h"
#include "Selection.hpp"

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
