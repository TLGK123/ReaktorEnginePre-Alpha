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

#include "ScreenWin.h"

#include <iostream>

#define DOCKING_ENABLED ImGui::GetIO().ConfigFlags & ImGuiConfigFlags_DockingEnable
using namespace std;
namespace TmingEngine
{
	unsigned int SCR_WIDTH = 1366;
	unsigned int SCR_HEIGHT = 768;

	unsigned int frame_width = 1366;
	unsigned int frame_height = 768;

	Camera EditorCamera(Vector3(0.0f, 0.0f, 5.0f));     //  Editor  Scene  camera
	glm::vec3 lightPos(1.2f, 1.0f, 2.0f);

	float lastX = SCR_WIDTH / 2.0f;
	float lastY = SCR_HEIGHT / 2.0f;
	bool firstMouse = true;

	// timing
	float deltaTime = 0.0f;
	float lastFrame = 0.0f;

	bool ScreenWin::Initialize()
	{
		cout << "Hello World" << endl;
		InitOpenGL();
		if (isEditorWindows)
		{
			InitImgui();
			InitWidgets();
		}
		return true;
	}

	void ScreenWin::WinRender()
	{
		done = false;
		SDL_Event event;
		while (SDL_PollEvent(&event))
		{
			if (isEditorWindows)
			{
				ImGui_ImplSDL2_ProcessEvent(&event);
			}

			if (event.type == SDL_QUIT)
				done = true;
			if (event.type == SDL_WINDOWEVENT && event.window.event == SDL_WINDOWEVENT_CLOSE && event.window.windowID == SDL_GetWindowID(window))
				done = true;
		}

		//float currentFrame = glfwGetTime();
		//deltaTime = currentFrame - lastFrame;
		//lastFrame = currentFrame;

		RenderFrameBuffer();

		glClearColor(0.2f, 0.2f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		glViewport(0, 0, 1366, 768);

		m_context->GetSubsystem<Engine>()->RenderScene();

		if (isEditorWindows)
		{
			Render_EditorUI();
		}

		SDL_GL_SwapWindow(window);
	}

	void ScreenWin::WinClose()
	{
	}

	bool ScreenWin::WinShouldClose()
	{
		return  done;
	}

	void ScreenWin::InitVertextData()
	{
	}

	void ScreenWin::InitTextureData()
	{
	}

	void ScreenWin::InitShader()
	{
	}

	void ScreenWin::InitModel()
	{
	}

	void ScreenWin::InitOpenGL()
	{
		// Setup SDL
		// (Some versions of SDL before <2.0.10 appears to have performance/stalling issues on a minority of Windows systems,
		// depending on whether SDL_INIT_GAMECONTROLLER is enabled or disabled.. updating to latest version of SDL is recommended!)
		if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER | SDL_INIT_GAMECONTROLLER) != 0)
		{
			IM_ASSERT("Error: %s\n", SDL_GetError());
			return;
		}

		// Decide GL+GLSL versions
#if __APPLE__
	// GL 3.2 Core + GLSL 150
		const char* glsl_version = "#version 150";
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_FLAGS, SDL_GL_CONTEXT_FORWARD_COMPATIBLE_FLAG); // Always required on Mac
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 2);
#else
	// GL 3.0 + GLSL 130
		const char* glsl_version = "#version 130";
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_FLAGS, 0);
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 0);
#endif

		// Create window with graphics context
		SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
		SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
		SDL_GL_SetAttribute(SDL_GL_STENCIL_SIZE, 8);
		SDL_WindowFlags window_flags = (SDL_WindowFlags)(SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE | SDL_WINDOW_ALLOW_HIGHDPI);
		window = SDL_CreateWindow("TmingEngine", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1366, 768, window_flags);
		SDL_GLContext gl_context = SDL_GL_CreateContext(window);
		SDL_GL_MakeCurrent(window, gl_context);
		SDL_GL_SetSwapInterval(1); // Enable vsync

		//glViewport(0, 0, 1366, 768);
		//glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
		//glfwSetCursorPosCallback(window, mouse_callback);
		//glfwSetScrollCallback(window, scroll_callback);

		// Initialize OpenGL loader----------------------
		bool err = gl3wInit() != 0;
		if (err)
		{
			IM_ASSERT(stderr, "Failed to initialize OpenGL loader!\n");
			return;
		}

		InitVertextData();
		InitTextureData();
		InitModel();
		InitShader();
		InitSkyBox();

		InitFrameBufer();

		int nrAttributes;
		glGetIntegerv(GL_MAX_VERTEX_ATTRIBS, &nrAttributes);
		std::cout << "顶点属性上限: " << nrAttributes << std::endl;
	}

	void ScreenWin::SetViewPoint(int startX, int startY, int width, int height)
	{
		glViewport(startX, startY, width, height);
		SCR_WIDTH = width;
		SCR_HEIGHT = height;
	}

	void ScreenWin::ChangeModel(string mpath)
	{
		//ourModel.Init(mpath);
	}

	void ScreenWin::RenderFrameBuffer()
	{
		glBindFramebuffer(GL_FRAMEBUFFER, framebuffer); //帧缓冲的 开始
		glEnable(GL_DEPTH_TEST);                        //后续所有渲染操作将渲染到当前绑定的帧缓存的附加缓存中
		glClearColor(0, 0, 0, 0);                       //由于我们的帧缓冲不是默认的帧缓存，渲染命令对窗口的视频输出不会产生任何影响。
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		glDisable(GL_DEPTH_TEST);
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
	}

	void ScreenWin::InitFrameBufer()
	{
		//创建一个帧缓冲对象，并绑定它
		//unsigned int framebuffer;
		glGenFramebuffers(1, &framebuffer);
		glBindFramebuffer(GL_FRAMEBUFFER, framebuffer);
		// 创建一个纹理图像
		//unsigned int textureColorbuffer;
		glGenTextures(1, &textureColorbuffer);
		glBindTexture(GL_TEXTURE_2D, textureColorbuffer);

		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, frame_width, frame_height, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		//纹理 附加到当前绑定的帧缓冲对象
		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, textureColorbuffer, 0);

		//创建一个渲染缓冲对象
		unsigned int rbo;
		glGenRenderbuffers(1, &rbo);
		glBindRenderbuffer(GL_RENDERBUFFER, rbo);
		//创建一个深度和模板渲染缓冲对象
		glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, frame_width, frame_height);
		//附加这个渲染缓冲对象：
		glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, rbo);

		if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
			cout << "ERROR::FRAMEBUFFER:: Framebuffer is not complete!" << endl;
		glBindFramebuffer(GL_FRAMEBUFFER, 0);

		CurrentFrameTextureID = textureColorbuffer;
		return;
	}

	void ScreenWin::ShutDown()
	{
		glDeleteVertexArrays(1, &VAO);
		glDeleteBuffers(1, &VBO);
		if (isEditorWindows)
		{
			// Cleanup
			ImGui_ImplOpenGL3_Shutdown();
			ImGui_ImplSDL2_Shutdown();
			ImGui::DestroyContext();
		}
		SDL_GL_DeleteContext(gl_context);
		SDL_DestroyWindow(window);
		SDL_Quit();
	}

	bool ScreenWin::ScreenShouldClose()
	{
		return done;
	}

	string initfile = FileSystem::getPath("Data/Setting/imgui.ini");

	void ScreenWin::InitImgui()
	{
		const char* glsl_version = "#version 150";
		// Setup Dear ImGui context
		IMGUI_CHECKVERSION();
		ImGui::CreateContext();
		ImGuiIO& io = ImGui::GetIO(); (void)io;
		io.IniFilename = initfile.c_str();

		io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
		io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
		io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;
		io.ConfigWindowsResizeFromEdges = true;
		io.ConfigViewportsNoTaskBarIcon = true;

		// Setup style
		ImGuiStyle& style = ImGui::GetStyle();
		if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
		{
			style.WindowRounding = 0.0f;
			style.Colors[ImGuiCol_WindowBg].w = 1.0f;
		}
		ApplyStyle();

		// Setup Platform/Renderer bindings
		ImGui_ImplSDL2_InitForOpenGL(window, gl_context);
		ImGui_ImplOpenGL3_Init(glsl_version);

		string fontpath = FileSystem::getPath("resources/font/SourceHanSansCN-Medium.ttf");
		ImFont* font = io.Fonts->AddFontFromFileTTF(fontpath.c_str(), 20.0f, NULL, io.Fonts->GetGlyphRangesChineseFull());
	}

	void ScreenWin::RenderSceneObjectForEditorCamera()
	{
	}

	void ScreenWin::Render_SkyBox_ForEditor()
	{
	}

	void ScreenWin::InitSkyBox()
	{
	}

	void ScreenWin::Render_EditorUI()
	{
		// Start the Dear ImGui frame
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplSDL2_NewFrame(window);
		ImGui::NewFrame();

		if (show_demo_window)
			ImGui::ShowDemoWindow(&show_demo_window);

		if (show_debug_window)
		{
			ShowDebugWindows(&show_debug_window);
		}

		if (show_another_window)
		{
			ImGui::Begin("Another Window", &show_another_window);
			ImGui::Text("Hello from another window!");
			if (ImGui::Button("Close Me"))
				show_another_window = false;
			ImGui::End();
		}
		ShowExampleAppDockSpace(&show_demo_window);

		//	bool showDebug = true;
		//	screenContext->GetSubsystem<Console>()->Draw("Hello Debug", &showDebug);
		//	screenContext->GetSubsystem<Console>()->Draw2("Hello Debug", &showDebug);

		//GetSubWidget<SceneView>()->ImageId = CurrentFrameTextureID;
		//GetSubWidget<Game>()->ImageId = 0;
		DrawScreenWidgets();

		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
		// Update and Render additional Platform Windows

		ImGuiIO& io = ImGui::GetIO(); (void)io;
		// Update and Render additional Platform Windows
		// (Platform functions may change the current OpenGL context, so we save/restore it to make it easier to paste this code elsewhere.
		//  For this specific demo app we could also call SDL_GL_MakeCurrent(window, gl_context) directly)
		if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
		{
			SDL_Window* backup_current_window = SDL_GL_GetCurrentWindow();
			SDL_GLContext backup_current_context = SDL_GL_GetCurrentContext();
			ImGui::UpdatePlatformWindows();
			ImGui::RenderPlatformWindowsDefault();
			SDL_GL_MakeCurrent(backup_current_window, backup_current_context);
		}
	}

	void ScreenWin::ApplyStyle()
	{
		// Color settings
		const auto text = ImVec4(0.76f, 0.77f, 0.8f, 1.0f);
		const auto white = ImVec4(1.0f, 1.0f, 1.0f, 1.0f);
		const auto black = ImVec4(0.0f, 0.0f, 0.0f, 1.0f);
		const auto background_very_dark = ImVec4(0.08f, 0.086f, 0.094f, 1.00f);
		const auto background_dark = ImVec4(0.117f, 0.121f, 0.145f, 1.00f);
		const auto background_medium = ImVec4(0.26f, 0.26f, 0.27f, 1.0f);
		const auto background_light = ImVec4(0.37f, 0.38f, 0.39f, 1.0f);
		const auto highlight_blue = ImVec4(0.172f, 0.239f, 0.341f, 1.0f);
		const auto highlight_blue_hovered = ImVec4(0.29f, 0.42f, 0.65f, 1.0f);
		const auto highlight_blue_active = ImVec4(0.382f, 0.449f, 0.561f, 1.0f);
		const auto bar_background = ImVec4(0.078f, 0.082f, 0.09f, 1.0f);
		const auto bar = ImVec4(0.164f, 0.180f, 0.231f, 1.0f);
		const auto bar_hovered = ImVec4(0.411f, 0.411f, 0.411f, 1.0f);
		const auto bar_active = ImVec4(0.337f, 0.337f, 0.368f, 1.0f);

		// Spatial settings
		const auto font_size = 24.0f;
		const auto font_scale = 0.7f;
		const auto roundness = 2.0f;

		// Use default black style as a base
		ImGui::StyleColorsDark();

		ImGuiStyle& style = ImGui::GetStyle();
		auto& io = ImGui::GetIO();

		// Spatial
		style.WindowBorderSize = 1.0f;
		style.FrameBorderSize = 0.0f;
		style.ScrollbarSize = 20.0f;
		style.FramePadding = ImVec2(5, 5);
		style.ItemSpacing = ImVec2(6, 5);
		style.WindowMenuButtonPosition = ImGuiDir_Right;
		style.WindowRounding = roundness;
		style.FrameRounding = roundness;
		style.PopupRounding = roundness;
		style.GrabRounding = roundness;
		style.ScrollbarRounding = roundness;
		style.Alpha = 1.0f;

		// Colors
		style.Colors[ImGuiCol_Text] = text;
		style.Colors[ImGuiCol_WindowBg] = background_dark;
		style.Colors[ImGuiCol_Border] = black;
		style.Colors[ImGuiCol_FrameBg] = bar;
		style.Colors[ImGuiCol_FrameBgHovered] = highlight_blue;
		style.Colors[ImGuiCol_FrameBgActive] = highlight_blue_hovered;
		style.Colors[ImGuiCol_TitleBg] = background_very_dark;
		style.Colors[ImGuiCol_TitleBgActive] = bar;
		style.Colors[ImGuiCol_MenuBarBg] = background_very_dark;
		style.Colors[ImGuiCol_ScrollbarBg] = bar_background;
		style.Colors[ImGuiCol_ScrollbarGrab] = bar;
		style.Colors[ImGuiCol_ScrollbarGrabHovered] = bar_hovered;
		style.Colors[ImGuiCol_ScrollbarGrabActive] = bar_active;
		style.Colors[ImGuiCol_CheckMark] = highlight_blue_hovered;
		style.Colors[ImGuiCol_SliderGrab] = highlight_blue_hovered;
		style.Colors[ImGuiCol_SliderGrabActive] = highlight_blue_active;
		style.Colors[ImGuiCol_Button] = bar_active;
		style.Colors[ImGuiCol_ButtonHovered] = highlight_blue;
		style.Colors[ImGuiCol_ButtonActive] = highlight_blue_active;
		style.Colors[ImGuiCol_Header] = highlight_blue; // selected items (tree, menu bar etc.)
		style.Colors[ImGuiCol_HeaderHovered] = highlight_blue_hovered; // hovered items (tree, menu bar etc.)
		style.Colors[ImGuiCol_HeaderActive] = highlight_blue_active;
		style.Colors[ImGuiCol_Separator] = background_light;
		style.Colors[ImGuiCol_ResizeGrip] = background_medium;
		style.Colors[ImGuiCol_ResizeGripHovered] = highlight_blue;
		style.Colors[ImGuiCol_ResizeGripActive] = highlight_blue_hovered;
		style.Colors[ImGuiCol_PlotLines] = ImVec4(0.0f, 0.7f, 0.77f, 1.0f);
		style.Colors[ImGuiCol_PlotHistogram] = highlight_blue; // Also used for progress bar
		style.Colors[ImGuiCol_PlotHistogramHovered] = highlight_blue_hovered;
		style.Colors[ImGuiCol_TextSelectedBg] = highlight_blue;
		style.Colors[ImGuiCol_PopupBg] = background_dark;
		style.Colors[ImGuiCol_DragDropTarget] = background_light;

		// Font
		//string dir_fonts = m_context->GetSubsystem<ResourceCache>()->GetDataDirectory(Asset_Fonts);
		//io.Fonts->AddFontFromFileTTF((dir_fonts + "CalibriBold.ttf").c_str(), font_size);
		//io.FontGlobalScale = font_scale;
	}

	//没有指定任何的Window就是创建到Debug Windows中
	void ScreenWin::ShowDebugWindows(bool* p_open)
	{
		static float f = 0.0f;
		static int counter = 0;
		static bool showLog = false;
		ImGui::Text("Hello, world!");                           // Display some text (you can use a format string too)
		ImGui::SliderFloat("float", &f, 0.0f, 1.0f);            // Edit 1 float using a slider from 0.0f to 1.0f
		ImGui::ColorEdit3("clear color", (float*)&clear_color); // Edit 3 floats representing a color

		ImGui::Checkbox("Demo Window", &show_demo_window);      // Edit bools storing our windows open/close state
		ImGui::Checkbox("Another Window", &show_another_window);

		if (ImGui::Button("Button"))                            // Buttons return true when clicked (NB: most widgets return true when edited/activated)
			counter++;

		//if (ImGui::Button("ShowLog"))
		//{
		//	showLog = true;
		//}

		ImGui::SameLine();
		ImGui::Text("counter = %d", counter);
		ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);

		ImGui::Image((void*)textureColorbuffer, ImVec2(320, 180), ImVec2(0, 0), ImVec2(-1, -1), ImColor(255, 255, 255, 255), ImColor(255, 255, 255, 128));

		if (ImGui::Button("Delete.."))
			ImGui::OpenPopup("Delete?");

		if (ImGui::BeginPopupModal("Delete?", NULL, ImGuiWindowFlags_AlwaysAutoResize))
		{
			ImGui::Text("All those beautiful files will be deleted.\nThis operation cannot be undone!\n\n");
			ImGui::Separator();

			//static int dummy_i = 0;
			//ImGui::Combo("Combo", &dummy_i, "Delete\0Delete harder\0");

			static bool dont_ask_me_next_time = false;
			ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2(0, 0));
			ImGui::Checkbox("Don't ask me next time", &dont_ask_me_next_time);
			ImGui::PopStyleVar();

			if (ImGui::Button("OK", ImVec2(120, 0))) { ImGui::CloseCurrentPopup(); }
			ImGui::SetItemDefaultFocus();
			ImGui::SameLine();
			if (ImGui::Button("Cancel", ImVec2(120, 0))) { ImGui::CloseCurrentPopup(); }
			ImGui::EndPopup();
		}
	}

	void ScreenWin::ShowExampleAppDockSpace(bool* p_open)
	{
		static bool opt_fullscreen_persistant = true;
		bool opt_fullscreen = opt_fullscreen_persistant;
		static ImGuiDockNodeFlags dockspace_flags = ImGuiDockNodeFlags_None;

		// We are using the ImGuiWindowFlags_NoDocking flag to make the parent window not dockable into,
		// because it would be confusing to have two docking targets within each others.
		ImGuiWindowFlags window_flags = ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoDocking;
		if (opt_fullscreen)
		{
			ImGuiViewport* viewport = ImGui::GetMainViewport();
			ImGui::SetNextWindowPos(viewport->Pos);
			ImGui::SetNextWindowSize(viewport->Size);
			ImGui::SetNextWindowViewport(viewport->ID);
			ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
			ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
			window_flags |= ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove;
			window_flags |= ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus;
		}

		// When using ImGuiDockNodeFlags_PassthruCentralNode, DockSpace() will render our background and handle the pass-thru hole, so we ask Begin() to not render a background.
		if (dockspace_flags & ImGuiDockNodeFlags_PassthruCentralNode)
			window_flags |= ImGuiWindowFlags_NoBackground;

		// Important: note that we proceed even if Begin() returns false (aka window is collapsed).
		// This is because we want to keep our DockSpace() active. If a DockSpace() is inactive,
		// all active windows docked into it will lose their parent and become undocked.
		// We cannot preserve the docking relationship between an active window and an inactive docking, otherwise
		// any change of dockspace/settings would lead to windows being stuck in limbo and never being visible.
		ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));
		ImGui::Begin("DockSpace Demo", p_open, window_flags);
		ImGui::PopStyleVar();

		if (opt_fullscreen)
			ImGui::PopStyleVar(2);

		// DockSpace
		ImGuiIO& io = ImGui::GetIO();
		if (io.ConfigFlags & ImGuiConfigFlags_DockingEnable)
		{
			ImGuiID dockspace_id = ImGui::GetID("MyDockSpace");
			ImGui::DockSpace(dockspace_id, ImVec2(0.0f, 0.0f), dockspace_flags);
		}
		else
		{
		}

		if (ImGui::BeginMenuBar())
		{
			if (ImGui::BeginMenu("File"))
			{
				// Disabling fullscreen would allow the window to be moved to the front of other windows,
				// which we can't undo at the moment without finer window depth/z control.
				//ImGui::MenuItem("Fullscreen", NULL, &opt_fullscreen_persistant);

				if (ImGui::MenuItem("Flag: NoSplit", "", (dockspace_flags & ImGuiDockNodeFlags_NoSplit) != 0))                 dockspace_flags ^= ImGuiDockNodeFlags_NoSplit;
				if (ImGui::MenuItem("Flag: NoResize", "", (dockspace_flags & ImGuiDockNodeFlags_NoResize) != 0))                dockspace_flags ^= ImGuiDockNodeFlags_NoResize;
				if (ImGui::MenuItem("Flag: NoDockingInCentralNode", "", (dockspace_flags & ImGuiDockNodeFlags_NoDockingInCentralNode) != 0))  dockspace_flags ^= ImGuiDockNodeFlags_NoDockingInCentralNode;
				if (ImGui::MenuItem("Flag: PassthruCentralNode", "", (dockspace_flags & ImGuiDockNodeFlags_PassthruCentralNode) != 0))     dockspace_flags ^= ImGuiDockNodeFlags_PassthruCentralNode;
				if (ImGui::MenuItem("Flag: AutoHideTabBar", "", (dockspace_flags & ImGuiDockNodeFlags_AutoHideTabBar) != 0))          dockspace_flags ^= ImGuiDockNodeFlags_AutoHideTabBar;
				ImGui::Separator();
				if (ImGui::MenuItem("Exit ", NULL, false, p_open != NULL))
				{
				}

				ImGui::EndMenu();
			}

			if (ImGui::BeginMenu("Window"))
			{
				/*if (ImGui::MenuItem("Profile"))
				{
					GetSubWidget<Profiler>()->Show();
				}
				if (ImGui::MenuItem("CodeEditor"))
				{
					GetSubWidget<CodeEditor>()->Show();
				}
				if (ImGui::MenuItem("DemoWindows"))
				{
					show_demo_window = true;
				}
				if (ImGui::MenuItem("DebugWindows"))
				{
					show_debug_window = true;
				}
				if (ImGui::MenuItem("Preview"))
				{
					GetSubWidget<Preview>()->Show();
				}*/
				ImGui::EndMenu();
			}

			ImGui::EndMenuBar();
		}

		ImGui::End();
	}

	//void framebuffer_size_callback(GLFWwindow* window, int width, int height)
	//{
	//	//glViewport(0, 0, frame_width, frame_height);
	//}

	//void mouse_callback(GLFWwindow* window, double xpos, double ypos)
	//{
	//	Global<Context>().GetSubsystem<ScreenWin>()->MouseMove(window, xpos, ypos);
	//}

	//void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
	//{
	//	Global<Context>().GetSubsystem<ScreenWin>()->MouseScroll(window, xoffset, yoffset);
	//}

	//void processInput(GLFWwindow* window)
	//{
	//	//if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
	//	//	glfwSetWindowShouldClose(window, true);

	//	//if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
	//	//	EditorCamera.ProcessKeyboard(FORWARD, deltaTime);
	//	//if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
	//	//	EditorCamera.ProcessKeyboard(BACKWARD, deltaTime);
	//	//if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
	//	//	EditorCamera.ProcessKeyboard(LEFT, deltaTime);
	//	//if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
	//	//	EditorCamera.ProcessKeyboard(RIGHT, deltaTime);
	//}

	//void ScreenWin::MouseMove(GLFWwindow* window, double xpos, double ypos)
	//{
	//	if (firstMouse)
	//	{
	//		lastX = xpos;
	//		lastY = ypos;
	//		firstMouse = false;
	//	}

	//	float xoffset = xpos - lastX;
	//	float yoffset = lastY - ypos; // reversed since y-coordinates go from bottom to top

	//	lastX = xpos;
	//	lastY = ypos;

	//	if (isEditorWindows)
	//	{
	//		ImGuiIO& io = ImGui::GetIO();

	//		if (&io != NULL && io.MouseDownDuration[1] >= 0)
	//		{
	//			//bool selected = GetSubWidget<SceneView>()->IsSceneviewFoucsed;
	//			//if (selected)
	//			//{
	//			//	EditorCamera.ProcessMouseMovement(xoffset, yoffset);
	//			//}
	//		}
	//	}
	//}

	//void ScreenWin::MouseScroll(GLFWwindow* window, double xoffset, double yoffset)
	//{
	//	ImGuiContext* c = ImGui::GetCurrentContext();

	//	//EditorCamera.ProcessMouseScroll(yoffset);
	//}
}