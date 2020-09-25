/*
			This file is part of:
				TmingEngine
			https://github.com/xiaomingfun/TmingEngine

   Copyright 2018 - 2020 TmingEngine

   File creator: littleblue

   TmingEngine is open-source software and you can redistribute it and/or modify
   it under the terms of the License; besides, anyone who use this file/software must include this copyright announcement.

   Licensed under the Apache License, Version 2.0 (the "License");
   you may not use this file except in compliance with the License.
   You may obtain a copy of the License at

	   http://www.apache.org/licenses/LICENSE-2.0

   Unless required by applicable law or agreed to in writing, software
   distributed under the License is distributed on an "AS IS" BASIS,
   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
   See the License for the specific language governing permissions and
   limitations under the License.
*/

#ifndef TmingEngine_Engine_Plantform_Windows_win_ScreenWin_h
#define TmingEngine_Engine_Plantform_Windows_win_ScreenWin_h

#include <SDL.h>
#include "GL/gl3w.h"
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
#include "ImGui/imgui_impl_sdl.h"


namespace TmingEngine
{
	//void framebuffer_size_callback(GLFWwindow* window, int width, int height);
	//void processInput(GLFWwindow* window);
	//void mouse_callback(GLFWwindow* window, double xpos, double ypos);
	//void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);

	class ScreenWin : public IWindows
	{
	public:
		SDL_GLContext gl_context;
		SDL_Window* window;
		unsigned int texture1, texture2, texture3;
		Shader screenShader;
		bool done = false;			//true close app£¬ when click X

		unsigned int VBO, VAO;

		bool Initialize()  override;
		void WinRender() override;
		void WinClose() override;
		bool WinShouldClose() override;
		void SetViewPoint(int startX, int startY, int width, int height) override;

		//vector<Widget*> m_widgets;

		bool show_debug_window = false;
		bool show_demo_window = true;
		bool show_another_window = false;
		ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);
		int CurrentFrameTextureID = 0;
		int CurrentFrameTextureIDCa = 0;

		unsigned int framebuffer;
		unsigned int textureColorbuffer;

		unsigned int framebufferCa;
		unsigned int textureColorbufferCa;

		void ShutDown();
		void ApplyStyle();
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

		//void MouseMove(GLFWwindow* window, double xpos, double ypos);
		//void MouseScroll(GLFWwindow* window, double xoffset, double yoffset);

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
