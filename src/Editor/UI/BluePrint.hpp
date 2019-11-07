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

#ifndef Game_hpp
#define Game_hpp
#include <stdio.h>
#include "Core/SubSystem.h"
#include "Core/Context.h"
#include "Widget.h"
#include "im.h"

# include "imgui_node_editor.h"
# define IMGUI_DEFINE_MATH_OPERATORS
# include "ImGui/imgui_internal.h"
namespace ed = ax::NodeEditor;


namespace TmingEngine
{
	// Struct to hold basic information about connection between
// pins. Note that connection (aka. link) has its own ID.
// This is useful later with dealing with selections, deletion
// or other operations.
	struct LinkInfo
	{
		ed::LinkId Id;
		ed::PinId  InputId;
		ed::PinId  OutputId;
	};



    class BluePrint :public Widget
    {
    public:
        
		BluePrint(Context *context)
        {
            m_title = "Game";
        }

		ed::EditorContext* g_Context = nullptr;    // Editor context, required to trace a editor state.
		bool                 g_FirstFrame = true;    // Flag set for first frame only, some action need to be executed once.
		ImVector<LinkInfo>   g_Links;                // List of live links. It is dynamic unless you want to create read-only view over nodes.
		int                  g_NextLinkId = 100;     // Counter to help generate link ids. In real application this will probably based on pointer to user data structure.

       
        void Begin();
        void Update();
        void End();
		void Application_Frame();
		void ImGuiEx_BeginColumn();
		void ImGuiEx_EndColumn();
		void ImGuiEx_NextColumn();
    };

}

#endif /* BluePrint */



