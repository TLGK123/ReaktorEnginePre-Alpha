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

#include "BluePrint.hpp"
using namespace TmingEngine;
void TmingEngine::BluePrint::Begin()
{
	ed::Config config;
	config.SettingsFile = "BasicInteraction.json";
	g_Context = ed::CreateEditor(&config);
}

void TmingEngine::BluePrint::Update()
{
	bool p_open = true;
	ImGui::SetNextWindowSize(ImVec2(640, 360), ImGuiCond_FirstUseEver);
	if (!ImGui::Begin("NodeEditor", &p_open))
	{
		ImGui::End();
		return;
	}
	Application_Frame();
	ImGui::End();
}

void TmingEngine::BluePrint::End()
{
	ed::DestroyEditor(g_Context);
}

void TmingEngine::BluePrint::Application_Frame()
{

	auto& io = ImGui::GetIO();

	ImGui::Text("FPS: %.2f (%.2gms)", io.Framerate, io.Framerate ? 1000.0f / io.Framerate : 0.0f);

	ImGui::Separator();

	ed::SetCurrentEditor(g_Context);

	// Start interaction with editor.
	ed::Begin("My Editor", ImVec2(0.0, 0.0f));

	int uniqueId = 1;

	//
	// 1) Commit known data to editor
	//

	// Submit Node A
	ed::NodeId nodeA_Id = uniqueId++;
	ed::PinId  nodeA_InputPinId = uniqueId++;
	ed::PinId  nodeA_OutputPinId = uniqueId++;

	if (g_FirstFrame)
		ed::SetNodePosition(nodeA_Id, ImVec2(10, 10));
	ed::BeginNode(nodeA_Id);
	ImGui::Text("Node A");
	ed::BeginPin(nodeA_InputPinId, ed::PinKind::Input);
	ImGui::Text("-> In");
	ed::EndPin();
	ImGui::SameLine();
	ed::BeginPin(nodeA_OutputPinId, ed::PinKind::Output);
	ImGui::Text("Out ->");
	ed::EndPin();
	ed::EndNode();

	// Submit Node B
	ed::NodeId nodeB_Id = uniqueId++;
	ed::PinId  nodeB_InputPinId1 = uniqueId++;
	ed::PinId  nodeB_InputPinId2 = uniqueId++;
	ed::PinId  nodeB_OutputPinId = uniqueId++;

	if (g_FirstFrame)
		ed::SetNodePosition(nodeB_Id, ImVec2(210, 60));
	ed::BeginNode(nodeB_Id);
	ImGui::Text("Node B");
	ImGuiEx_BeginColumn();
	ed::BeginPin(nodeB_InputPinId1, ed::PinKind::Input);
	ImGui::Text("-> In1");
	ed::EndPin();
	ed::BeginPin(nodeB_InputPinId2, ed::PinKind::Input);
	ImGui::Text("-> In2");
	ed::EndPin();
	ImGuiEx_NextColumn();
	ed::BeginPin(nodeB_OutputPinId, ed::PinKind::Output);
	ImGui::Text("Out ->");
	ed::EndPin();
	ImGuiEx_EndColumn();
	ed::EndNode();

	// Submit Links
	for (auto& linkInfo : g_Links)
		ed::Link(linkInfo.Id, linkInfo.InputId, linkInfo.OutputId);

	//
	// 2) Handle interactions
	//

	// Handle creation action, returns true if editor want to create new object (node or link)
	if (ed::BeginCreate())
	{
		ed::PinId inputPinId, outputPinId;
		if (ed::QueryNewLink(&inputPinId, &outputPinId))
		{
			// QueryNewLink returns true if editor want to create new link between pins.
			//
			// Link can be created only for two valid pins, it is up to you to
			// validate if connection make sense. Editor is happy to make any.
			//
			// Link always goes from input to output. User may choose to drag
			// link from output pin or input pin. This determine which pin ids
			// are valid and which are not:
			//   * input valid, output invalid - user started to drag new ling from input pin
			//   * input invalid, output valid - user started to drag new ling from output pin
			//   * input valid, output valid   - user dragged link over other pin, can be validated

			if (inputPinId && outputPinId) // both are valid, let's accept link
			{
				// ed::AcceptNewItem() return true when user release mouse button.
				if (ed::AcceptNewItem())
				{
					// Since we accepted new link, lets add one to our list of links.
					g_Links.push_back({ ed::LinkId(g_NextLinkId++), inputPinId, outputPinId });

					// Draw new link.
					ed::Link(g_Links.back().Id, g_Links.back().InputId, g_Links.back().OutputId);
				}

				// You may choose to reject connection between these nodes
				// by calling ed::RejectNewItem(). This will allow editor to give
				// visual feedback by changing link thickness and color.
			}
		}
	}
	ed::EndCreate(); // Wraps up object creation action handling.


	// Handle deletion action
	if (ed::BeginDelete())
	{
		// There may be many links marked for deletion, let's loop over them.
		ed::LinkId deletedLinkId;
		while (ed::QueryDeletedLink(&deletedLinkId))
		{
			// If you agree that link can be deleted, accept deletion.
			if (ed::AcceptDeletedItem())
			{
				// Then remove link from your data.
				for (auto& link : g_Links)
				{
					if (link.Id == deletedLinkId)
					{
						g_Links.erase(&link);
						break;
					}
				}
			}

			// You may reject link deletion by calling:
			// ed::RejectDeletedItem();
		}
	}
	ed::EndDelete(); // Wrap up deletion action



	// End of interaction with editor.
	ed::End();

	if (g_FirstFrame)
		ed::NavigateToContent(0.0f);

	ed::SetCurrentEditor(nullptr);

	g_FirstFrame = false;

	// ImGui::ShowMetricsWindow();

}

const char* Application_GetName()
{
	return "Basic Interaction";
}


void TmingEngine::BluePrint::ImGuiEx_BeginColumn()
{
	ImGui::BeginGroup();
}

void TmingEngine::BluePrint::ImGuiEx_NextColumn()
{
	ImGui::EndGroup();
	ImGui::SameLine();
	ImGui::BeginGroup();
}

void TmingEngine::BluePrint::ImGuiEx_EndColumn()
{
	ImGui::EndGroup();
}




