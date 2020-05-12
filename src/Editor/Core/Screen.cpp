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

#include "Screen.h"
#include <iostream>
#include "Stb_Image/stb_image.h"

using namespace std;
using namespace TmingEngine;

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
	InitImgui();
	InitEditorWidget(m_context);
	return true;
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

	if (!glfwInit())
	{
		IM_ASSERT(false && "glfwInit()  failure");
		return;
	}


	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);            // uncomment this statement to fix compilation on OS X
#endif

	window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "TmingEngine", NULL, NULL);
	if (window == NULL)
	{
		IM_ASSERT("Failed to create GLFW window");
		glfwTerminate();
		return;
	}
	//IM_ASSERT(1 > 3 && "Failed to test IM_ASSERT");
	glfwMakeContextCurrent(window);
	glfwSwapInterval(1); // Enable vsync  开启垂直同步 游戏最大帧率和显示器刷新帧率一致

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return;
	}

	glViewport(0, 0, 1366, 768);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
	glfwSetCursorPosCallback(window, mouse_callback);
	glfwSetScrollCallback(window, scroll_callback);

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

void ScreenWin::InitEditorWidget(Context* context)
{
	//context->RegisterSubsystem(new Console(context));

	RegisteWidget(new SceneView(context));
	//	RegisteWidget(new DemoMenu(context));
	RegisteWidget(new Project(context));
	RegisteWidget(new Hierachy(context));
	RegisteWidget(new Inspector(context));
	RegisteWidget(new Game(context));
	RegisteWidget(new Profiler(context));
	RegisteWidget(new Console(context));
	RegisteWidget(new CodeEditor(context));
	RegisteWidget(new Preview(context));
	Debug::Log(" Editor 初始化窗口成功  ");

	InitWidgets();
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


void ScreenWin::Update()
{
	
	glfwPollEvents();

	float currentFrame = glfwGetTime();
	deltaTime = currentFrame - lastFrame;
	lastFrame = currentFrame;
	processInput(window);
	RenderFrameBuffer();

	glClearColor(0.2f, 0.2f, 0.3f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);
	glViewport(0, 0, 1366, 768);



	Render_EditorUI();

	glfwSwapBuffers(window);
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
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();

	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glfwDestroyWindow(window);
	glfwTerminate();
}

bool ScreenWin::ScreenShouldClose()
{
	return glfwWindowShouldClose(window);
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

	io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;       // Enable Keyboard Controls
	//io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls
	io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;           // Enable Docking
	io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;         // Enable Multi-Viewport / Platform Windows
	//io.ConfigViewportsNoAutoMerge = true;
	//io.ConfigViewportsNoTaskBarIcon = true;

	// Setup style
	ImGuiStyle& style = ImGui::GetStyle();
	if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
	{
		style.WindowRounding = 0.0f;
		style.Colors[ImGuiCol_WindowBg].w = 1.0f;
	}

	ImGui_ImplGlfw_InitForOpenGL(window, true);
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
	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplGlfw_NewFrame();
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

	GetSubWidget<SceneView>()->ImageId = CurrentFrameTextureID;
	GetSubWidget<Game>()->ImageId = 0;
	DrawScreenWidgets();

	ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

	// Update and Render additional Platform Windows
	// (Platform functions may change the current OpenGL context, so we save/restore it to make it easier to paste this code elsewhere.
	//  For this specific demo app we could also call glfwMakeContextCurrent(window) directly)
	ImGuiIO& io = ImGui::GetIO();
	if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
	{
		GLFWwindow* backup_current_context = glfwGetCurrentContext();
		ImGui::UpdatePlatformWindows();
		ImGui::RenderPlatformWindowsDefault();
		glfwMakeContextCurrent(backup_current_context);
	}
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
			if (ImGui::MenuItem("Profile"))
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
			}
			ImGui::EndMenu();
		}

		ImGui::EndMenuBar();
	}

	ImGui::End();
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	//glViewport(0, 0, frame_width, frame_height);
}



void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
	Global<Context>().GetSubsystem<ScreenWin>()->MouseMove(window, xpos, ypos);
}

void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
	Global<Context>().GetSubsystem<ScreenWin>()->MouseScroll(window, xoffset, yoffset);
}


void processInput(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);

	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		EditorCamera.ProcessKeyboard(FORWARD, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		EditorCamera.ProcessKeyboard(BACKWARD, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		EditorCamera.ProcessKeyboard(LEFT, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		EditorCamera.ProcessKeyboard(RIGHT, deltaTime);
}

void ScreenWin::MouseMove(GLFWwindow* window, double xpos, double ypos)
{
	if (firstMouse)
	{
		lastX = xpos;
		lastY = ypos;
		firstMouse = false;
	}

	float xoffset = xpos - lastX;
	float yoffset = lastY - ypos; // reversed since y-coordinates go from bottom to top

	lastX = xpos;
	lastY = ypos;

	ImGuiIO& io = ImGui::GetIO();

	if (&io != NULL && io.MouseDownDuration[1] >= 0)
	{
		bool selected = GetSubWidget<SceneView>()->IsSceneviewFoucsed;
		if (selected)
		{
			EditorCamera.ProcessMouseMovement(xoffset, yoffset);
		}
	}
}

void ScreenWin::MouseScroll(GLFWwindow* window, double xoffset, double yoffset)
{
	ImGuiContext* c = ImGui::GetCurrentContext();

	//EditorCamera.ProcessMouseScroll(yoffset);
}
