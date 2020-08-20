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

#include "Profiler.hpp"

namespace TmingEngine
{
	Profiler::~Profiler()
	{
	}

	void Profiler::Begin()
	{
		p_open = false;
	}

	void Profiler::Update()
	{
		if (!p_open)
		{
			return;
		}

		ImGui::SetNextWindowSize(ImVec2(350, 180), ImGuiCond_FirstUseEver);
		if (!ImGui::Begin("Profiler", &p_open))
		{
			ImGui::End();
			return;
		}

		{
			static bool animate = true;
			ImGui::Checkbox("Animate", &animate);

			static float values[90] = { 0 };
			static int values_offset = 0;
			static double refresh_time = 0.0;
			if (!animate || refresh_time == 0.0)
				refresh_time = ImGui::GetTime();
			while (refresh_time < ImGui::GetTime()) // Create dummy data at fixed 60 hz rate for the demo
			{
				static float phase = 0.0f;
				values[values_offset] = cosf(phase);
				values_offset = (values_offset + 1) % IM_ARRAYSIZE(values);
				phase += 0.10f * values_offset;
				refresh_time += 1.0f / 5.0f;
			}
			ImGui::PlotLines("Lines", values, IM_ARRAYSIZE(values), values_offset, "avg 0.0", -1.0f, 1.0f, ImVec2(0, 160));
		}

		ImGui::End();

		//static ImNodes::CanvasState canvas{};
		//const ImGuiStyle& style = ImGui::GetStyle();
		//if (ImGui::Begin("ImNodes", nullptr, ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoScrollWithMouse))
		//{
		//    // We probably need to keep some state, like positions of nodes/slots for rendering connections.
		//    ImNodes::BeginCanvas(&canvas);
		//    for (auto it = nodes.begin(); it != nodes.end();)
		//    {
		//        MyNode* node = *it;
		//
		//        // Start rendering node
		//        if (ImNodes::Ez::BeginNode(node, node->title, &node->pos, &node->selected))
		//        {
		//            // Render input nodes first (order is important)
		//            ImNodes::Ez::InputSlots(node->input_slots.data(), node->input_slots.size());
		//
		//            // Custom node content may go here
		//            ImGui::Text("Content of %s", node->title);
		//
		//            // Render output nodes first (order is important)
		//            ImNodes::Ez::OutputSlots(node->output_slots.data(), node->output_slots.size());
		//
		//            // Store new connections when they are created
		//            Connection new_connection;
		//            if (ImNodes::GetNewConnection(&new_connection.input_node, &new_connection.input_slot,
		//                                          &new_connection.output_node, &new_connection.output_slot))
		//            {
		//                ((MyNode*) new_connection.input_node)->connections.push_back(new_connection);
		//                ((MyNode*) new_connection.output_node)->connections.push_back(new_connection);
		//            }
		//
		//            // Render output connections of this node
		//            for (const Connection& connection : node->connections)
		//            {
		//                // Node contains all it's connections (both from output and to input slots). This means that multiple
		//                // nodes will have same connection. We render only output connections and ensure that each connection
		//                // will be rendered once.
		//                if (connection.output_node != node)
		//                    continue;
		//
		//                if (!ImNodes::Connection(connection.input_node, connection.input_slot, connection.output_node,
		//                                         connection.output_slot))
		//                {
		//                    // Remove deleted connections
		//                    ((MyNode*) connection.input_node)->DeleteConnection(connection);
		//                    ((MyNode*) connection.output_node)->DeleteConnection(connection);
		//                }
		//            }
		//        }
		//        // Node rendering is done. This call will render node background based on size of content inside node.
		//        ImNodes::Ez::EndNode();
		//
		//        if (node->selected && ImGui::IsKeyPressedMap(ImGuiKey_Delete))
		//        {
		//            for (auto& connection : node->connections)
		//            {
		//                ((MyNode*) connection.input_node)->DeleteConnection(connection);
		//                ((MyNode*) connection.output_node)->DeleteConnection(connection);
		//            }
		//            delete node;
		//            it = nodes.erase(it);
		//        }
		//        else
		//            ++it;
		//    }
		//
		//    const ImGuiIO& io = ImGui::GetIO();
		//    if (ImGui::IsMouseReleased(1) && ImGui::IsWindowHovered() && !ImGui::IsMouseDragging(1))
		//    {
		//        ImGui::FocusWindow(ImGui::GetCurrentWindow());
		//        ImGui::OpenPopup("NodesContextMenu");
		//    }
		//
		//    if (ImGui::BeginPopup("NodesContextMenu"))
		//    {
		//        for (const auto& desc : available_nodes)
		//        {
		//            if (ImGui::MenuItem(desc.first.c_str()))
		//            {
		//                nodes.push_back(desc.second());
		//                ImNodes::AutoPositionNode(nodes.back());
		//            }
		//        }
		//        ImGui::Separator();
		//        if (ImGui::MenuItem("Reset Zoom"))
		//            canvas.zoom = 1;
		//
		//        if (ImGui::IsAnyMouseDown() && !ImGui::IsWindowHovered())
		//            ImGui::CloseCurrentPopup();
		//        ImGui::EndPopup();
		//    }
		//
		//    ImNodes::EndCanvas();
		//}
		//ImGui::End();
	}

	void Profiler::End()
	{
	}
}// namespace TmingEngine