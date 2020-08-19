//The MIT License
//
//Copyright(c) 2016 - 2020 littleblue
//
//Permission is hereby granted, free of charge, to any person obtaining a copy
//of this softwareand associated documentation files(the "Software"), to deal
//in the Software without restriction, including without limitation the rights
//to use, copy, modify, merge, publish, distribute, sublicense, and / or sell
//copies of the Software, and to permit persons to whom the Software is furnished
//to do so, subject to the following conditions :
//
//The above copyright noticeand this permission notice shall be included in
//all copies or substantial portions of the Software.
//
//THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
//IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS
//FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.IN NO EVENT SHALL THE AUTHORS OR
//COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER
//IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
//CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

#ifndef TmingEngine_Engine_Plantform_Windows_win_ScreenWin_h
#define TmingEngine_Engine_Plantform_Windows_win_ScreenWin_h

//#include "im.h"
#include "GLFW/glfw3.h"
#include "Stb_Image/stb_image.h"
#include "Core/Context.h"
#include "Core/Engine.h"
#include "Core/Log.h"
#include "Core/Math/Radian.h"
#include "Core/Math/Matrix.h"

#include "Rendering/RHI/IShader.hpp"
#include "Rendering/OpenGL/OpenGLShader.hpp"
#include "Rendering/Camera.hpp"
#include "Plantform/Windows/IWindows.h"

#include "ImGui/imgui_impl_opengl3.h"
#include "ImGui/imgui_impl_glfw.h"

namespace TmingEngine
{
	void framebuffer_size_callback(GLFWwindow* window, int width, int height);
	void processInput(GLFWwindow* window);
	void mouse_callback(GLFWwindow* window, double xpos, double ypos);
	void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);

	class ScreenWin : public IWindows
	{
	public:
		GLFWwindow* window;
		unsigned int texture1, texture2, texture3;
		Shader screenShader;

		unsigned int VBO, VAO;

		void WinInitialize()  override;
		void WinRender() override;
		void WinClose() override;
		bool WinShouldClose() override;
		void SetViewPoint(int startX, int startY, int width, int height) override;

		//vector<Widget*> m_widgets;

		bool show_debug_window = false;
		bool show_demo_window = false;
		bool show_another_window = false;
		ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);
		int CurrentFrameTextureID = 0;
		int CurrentFrameTextureIDCa = 0;

		unsigned int framebuffer;
		unsigned int textureColorbuffer;

		unsigned int framebufferCa;
		unsigned int textureColorbufferCa;

		void ShutDown();

		bool ScreenShouldClose();

		void InitOpenGL();
		void InitShader();
		void InitModel();
		void InitVertextData();
		void InitTextureData();

		void ChangeModel(string mpath);
		int GetCurrentFrameTexture();
		void InitFrameBufer();
		void CreateFrameBuferCa();
		void RenderFrameBuffer();
		void ShowExampleAppDockSpace(bool* p_open);
		void ShowDebugWindows(bool* p_open);

		void MouseMove(GLFWwindow* window, double xpos, double ypos);
		void MouseScroll(GLFWwindow* window, double xoffset, double yoffset);

		ScreenWin(Context* context) : IWindows(context)
		{
		}

		void InitWidgets()
		{
			if (InsertEditorWidget != nullptr)
			{
				InsertEditorWidget();
			}

			for (auto& widget : m_widgets)
			{
				if (widget->GetIsWindow())
				{
					widget->Begin();
				}
			}
		}

		~ScreenWin()
		{
			//for (auto& widget : m_widgets)
			//{
			//	if (widget->GetIsWindow())
			//	{
			//		widget->End();
			//	}
			//}
		}

		//void RegisteWidget(Widget* widget)
		//{
		//	m_widgets.push_back(widget);
		//}

		//template <class T>
		//T* GetSubWidget()
		//{
		//	for (const auto& subwidget : m_widgets)
		//	{
		//		if (typeid(T) == typeid(*subwidget))
		//			return static_cast<T*>(subwidget);
		//	}
		//	return nullptr;
		//}

		//void DrawScreenWidgets()
		//{
		//	for (auto& widget : m_widgets)
		//	{
		//		widget->Update();
		//	}
		//}

	private:
		void InitImgui();
		void RenderSceneObjectForEditorCamera();
		void Render_SceneObjectForGameCamera();
		void InitSkyBox();
		void Render_SkyBox_ForGame();
		void Render_SkyBox_ForEditor();
		void Render_EditorUI();
	};
}
#endif // TmingEngine_Engine_Plantform_Windows_win_ScreenWin_h
