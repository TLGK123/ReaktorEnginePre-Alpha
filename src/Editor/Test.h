#pragma once

#include "Core/SubSystem.h"
#include "Core/Context.h"
#include "imgui.h"
#include "imgui_impl_glfw_gl3.h"


class TestDemo
{
public:
	TestDemo()
	{

	}
	~TestDemo()
	{

	}
	virtual void Render_SceneObject();
private:

};

class Demo1 :public TestDemo
{
public:
	Demo1()
	{
	}

	~Demo1()
	{
	}

	void Render_SceneObject() override;

private:

};

class Demo2 :public TestDemo
{
public:
	Demo2()
	{
	}

	~Demo2()
	{
	}

	void Render_SceneObject() override;

private:

};


