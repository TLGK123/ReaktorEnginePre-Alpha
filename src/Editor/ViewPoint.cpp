#include "ViewPoint.h"

TmingEngine::ViewPoint::~ViewPoint()
{

}

void TmingEngine::ViewPoint::Begin()
{

	//Debug::Log("# 1");
	//ImGui::SetNextWindowSize(ImVec2(500, 400), ImGuiCond_FirstUseEver);
	//Debug::Log("# 2");
	//ImGui::SetNextWindowSizeConstraints(ImVec2(m_xMin, m_yMin), ImVec2(m_xMax, m_yMax));
	//Debug::Log("# 3");
	//ImGui::Begin(m_title.c_str(), &m_isVisible, m_windowFlags);
	//const ImTextureID tex_id = ImGui::GetIO().Fonts->TexID;
	//ImGui::Image(tex_id, ImVec2(250, 200), ImVec2(0, 0), ImVec2(1, 1), ImColor(255, 255, 255, 255), ImColor(255, 255, 255, 128));
}

void TmingEngine::ViewPoint::Update()
{
	bool p_open = true;
	ImGui::SetNextWindowSize(ImVec2(350, 560), ImGuiCond_FirstUseEver);
	if (!ImGui::Begin("Scene", &p_open))
	{
		ImGui::End();
		return;
	}
	ImGuiIO& io = ImGui::GetIO();

	// Here we are grabbing the font texture because that's the only one we have access to inside the demo code.
	// Remember that ImTextureID is just storage for whatever you want it to be, it is essentially a value that will be passed to the render function inside the ImDrawCmd structure.
	// If you use one of the default imgui_impl_XXXX.cpp renderer, they all have comments at the top of their file to specify what they expect to be stored in ImTextureID.
	// (for example, the imgui_impl_dx11.cpp renderer expect a 'ID3D11ShaderResourceView*' pointer. The imgui_impl_glfw_gl3.cpp renderer expect a GLuint OpenGL texture identifier etc.)
	// If you decided that ImTextureID = MyEngineTexture*, then you can pass your MyEngineTexture* pointers to ImGui::Image(), and gather width/height through your own functions, etc.
	// Using ShowMetricsWindow() as a "debugger" to inspect the draw data that are being passed to your render will help you debug issues if you are confused about this.
	// Consider using the lower-level ImDrawList::AddImage() API, via ImGui::GetWindowDrawList()->AddImage().
	// ImTextureID my_tex_id = io.Fonts->TexID;
	ImTextureID my_tex_id =(void *)ImageId;
	
	float my_tex_w = 1366;
	float my_tex_h = 768;

	ImGui::Text("%.0fx%.0f", my_tex_w, my_tex_h);
	//----------------------------------------------------------------- -1 -1  Image reversal
	ImGui::Image(my_tex_id, ImVec2(my_tex_w, my_tex_h), ImVec2(0, 0), ImVec2(-1, -1), ImColor(255, 255, 255, 255), ImColor(255, 255, 255, 128));
	ImGui::End();
	
}

void TmingEngine::ViewPoint::End()
{
//	ImGui::End();
}

void TmingEngine::ViewPoint::SetTexture(int Id)
{
	ImageId = Id;
}