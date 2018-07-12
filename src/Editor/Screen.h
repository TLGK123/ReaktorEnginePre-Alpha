#ifndef Screen_h
#define Screen_h

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
#include "UI\Widgets\Widget.h"
#include "ViewPoint.h"
#include "Log\Log.h"

//#if Debug
//#pragma comment( linker, "/subsystem:\"windows\" /entry:\"mainCRTStartup\"" ) // 去掉黑色控制台窗口
//#endif //  Debug

void framebuffer_size_callback(GLFWwindow* window, int width, int height);  //函数声明，当窗口大小调整时触发的函数
void processInput(GLFWwindow *window);                                      //处理按键输入的函数

void mouse_callback(GLFWwindow* window, double xpos, double ypos);          //鼠标处理函数
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);   //滚轮处理函数

using namespace TmingEngine;
class Screen :public Subsystem
{
public:
	GLFWwindow * window;
	unsigned int texture1, texture2;
	Shader ourShader;
	unsigned int VBO, VAO;
	vector<Widget *> m_widgets;

	bool show_demo_window = true;
	bool show_another_window = false;
	ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);
	Context * screenContext;
	int CurrentFrameTextureID = 0;

	unsigned int framebuffer;
	unsigned int textureColorbuffer;


	void Initialize(Context * context);
	void Update();
	void ShutDown();

	bool ScreenShouldClose();

	void InitOpenGL();

	void InitSubSystem(Context * context);

	int GetCurrentFrameTexture();

	void CreateFrameBufer();
	 
	Screen(Context* context) : Subsystem(context)
	{
		Initialize(context);
	}

	void RegisteWidget(Widget *widget )
	{
		m_widgets.push_back(widget);
	}

	void DrawScreen()
	{
		for (auto& widget : m_widgets)
		{
			if (widget->GetIsWindow())
			{
				widget->Begin();
			}

			widget->Update();

			if (widget->GetIsWindow())
			{
				widget->End();
			}
		}
	}

	void CreateCube();
private:
	void InitImgui();
	void Render_SceneObject();
	void Render_SkyBox();
	void Render_UI();

};

#endif // 