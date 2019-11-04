#include "Widget.h"
using namespace TmingEngine;

void Widget::Initialize(Context* context)
{
	m_windowFlags = ImGuiWindowFlags_None;
	m_context = context;

	m_xMin = 455;
	m_yMin = 400;
	m_xMax = FLT_MAX;
	m_yMax = FLT_MAX;
}

void Widget::Begin()
{
}

void Widget::End()
{
}
