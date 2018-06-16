#pragma once
#include <string>
#include"../Core/Context.h"

class Widget
{
public:
	virtual ~Widget() {}
	virtual void Initialize(TmingEngine::Context* context);
	virtual void Begin();
	virtual void Update() = 0;
	virtual void End();
	bool GetIsWindow() { return m_isWindow; }

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
