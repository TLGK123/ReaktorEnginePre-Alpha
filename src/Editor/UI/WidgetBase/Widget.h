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
		void Show() { m_isVisible = true; };
		void Hide() { m_isVisible = false; };

	protected:
		TmingEngine::Context* m_context = nullptr;
		bool m_isVisible = false;
		bool m_isWindow = true;
		std::string m_title;
		int m_windowFlags = 0;
		float m_xMin = 0;
		float m_xMax = 0;
		float m_yMin = 0;
		float m_yMax = 0;
	};
}
