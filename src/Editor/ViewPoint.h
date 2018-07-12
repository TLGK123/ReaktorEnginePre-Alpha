#pragma once
#include "Core/SubSystem.h"
#include "Core/Context.h"
#include "imgui.h"
#include "imgui_impl_glfw_gl3.h"
#include "Log/Log.h"
#include "UI/Widgets/Widget.h"

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
		void CreateCube();
	};
}