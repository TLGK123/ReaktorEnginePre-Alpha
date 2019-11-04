//The MIT License
//
//Copyright(c) 2016 - 2019 littleblue
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

#ifndef Screen_h

#define Screen_h

#include "im.h"
#include "Core/Context.h"
#include "Console.h"
#include "Widget.h"
#include "SceneView.h"
//#include "DemoMenu.h"
//#include "demo.h"
#include "Project.h"
#include "Hierachy.h"
#include "Inspector.hpp"
#include "Game.hpp"
#include "Profiler.hpp"
#include "Console.h"
#include "CodeEditor.h"
#include "Preview.hpp"
#include "Rendering/Camera.hpp"
#include "Core/Math/Radian.h"
#include "Core/Math/Matrix.h"
#include "Core/Log/Log.h"

//#if Debug
//#pragma comment( linker, "/subsystem:\"windows\" /entry:\"mainCRTStartup\"" )

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow *window);

void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);




using namespace TmingEngine;

class ScreenSystem :public Subsystem
{
public:
	GLFWwindow * window;
	unsigned int texture1, texture2;
	Shader ourShader , skyboxShader;
    Shader lightingShader;
    Shader lampShader;
    Shader OutLineShader;
	unsigned int VBO, VAO ;
    
    unsigned int skyboxVAO, skyboxVBO;
    unsigned int lightVAO;
    unsigned int cubemapTexture;
    bool Initialize() override;
	vector<Widget *> m_widgets;

    Model ourModel;
//	vector<DemoTest *> m_testDemos;

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

	void Update();
	void ShutDown();

	bool ScreenShouldClose();

	void InitOpenGL();
    void InitShader();
    void InitModel();
    void InitVertextData();
    void InitTextureData();


	void InitEditorWidget(Context * context);

	int GetCurrentFrameTexture();
	void InitFrameBufer();
    void CreateFrameBuferCa();
    void RenderFrameBuffer();
	void ShowExampleAppDockSpace(bool* p_open);
	void ShowDebugWindows(bool* p_open);

	ScreenSystem(Context* context) : Subsystem(context)
	{
		context->RegisterSubsystem(this);

	}

	void InitWidgets()
	{
		for (auto& widget : m_widgets)
		{
			if (widget->GetIsWindow())
			{
				widget->Begin();
			}
		}
	}
    
    ~ScreenSystem()
    {
        for (auto& widget : m_widgets)
        {
            if (widget->GetIsWindow())
            {
                widget->End();
            }
        }
        
    }

	void RegisteWidget(Widget *widget)
	{
		m_widgets.push_back(widget);
	}

	template <class T>
	T* GetSubWidget()
	{
		for (const auto& subwidget : m_widgets)
		{
			if (typeid(T) == typeid(*subwidget))
				return static_cast<T*>(subwidget);
		}
		return nullptr;
	}

	void DrawScreen()
	{
		for (auto& widget : m_widgets)
		{
			widget->Update();
		}
	}


private:
	void InitImgui();
	void RenderSceneObjectForEditorCamera();
    void Render_SceneObjectForGameCamera();
	void InitSkyBox();
    void Render_SkyBox_ForGame();
    void Render_SkyBox_ForEditor();
	void Render_EditorUI();
};

#endif // 
