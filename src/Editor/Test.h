#pragma once
#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <learnopengl/shader_m.h>
#include <learnopengl/camera.h>
#include <learnopengl/model.h>
#include <iostream>

#include "imgui.h"
#include "imgui_impl_glfw_gl3.h"

#include "Core/Context.h"
#include "Console.h"
#include "UI/Widgets/Widget.h"
#include "ViewPoint.h"
#include "DemoMenu.h"
#include "Log/Log.h"

namespace TmingEngine
{
	class TestDemo
	{
	public:
		TestDemo();
		~TestDemo();
		void Render_SceneObject();
	private:

	};
}



