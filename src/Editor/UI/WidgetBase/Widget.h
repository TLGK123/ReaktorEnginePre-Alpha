#pragma once
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
		virtual void Update() = 0;
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
		float m_xMin = 0;
		float m_xMax = 0;
		float m_yMin = 0;
		float m_yMax = 0;
	};
}
