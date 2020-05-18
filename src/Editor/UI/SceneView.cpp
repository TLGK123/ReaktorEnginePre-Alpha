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


#include "SceneView.h"

namespace TmingEngine
{
  


TmingEngine::SceneView::~SceneView()
{
}

void TmingEngine::SceneView::Begin()
{
    
}

int lastSceneX = -1;
int lastSceneY = -1;

void TmingEngine::SceneView::Update()
{
	bool p_open = true;
	ImGui::SetNextWindowSize(ImVec2(650, 375), ImGuiCond_FirstUseEver);
	if (!ImGui::Begin("Scene", &p_open))
	{
		ImGui::End();
		return;
	}
	IsSceneviewFoucsed = ImGui::IsWindowFocused();
	ImTextureID my_tex_id = (void *)ImageId;
	float my_tex_w = ImGui::GetWindowSize().x - 0;
	float my_tex_h = ImGui::GetWindowSize().y - 0;

	//ImGui::Text(" Scene  %.0fx%.0f", my_tex_w, my_tex_h);

	auto s = ImGui::GetWindowViewport();
	//if (lastSceneX != my_tex_w || lastSceneY != my_tex_h)
	//{
	//	if (lastSceneX != -1 || lastSceneY != -1)
	//	{
	//		Global<Context>().GetSubsystem<ScreenSystem>()->SetViewPoint(s->Pos.x, s->Pos.y, s->Size.x, s->Size.y);
	//	}

	//	lastSceneX = my_tex_w;
	//	lastSceneY = my_tex_h;
	//}
	Global<Context>().GetSubsystem<Engine>()->windows->SetViewPoint(s->Pos.x, s->Pos.y, s->Size.x, s->Size.y);
	//----------------------------------------------------------------- -1 -1  Image reversal
	ImGui::Image(my_tex_id, ImVec2(my_tex_w, my_tex_h), ImVec2(0, 0), ImVec2(-1, -1), ImColor(255, 255, 255, 255), ImColor(255, 255, 255, 128));
	ImGui::End();
}

void TmingEngine::SceneView::End()
{
}

void TmingEngine::SceneView::SetTexture(int Id)
{
	ImageId = Id;
}
    
}
