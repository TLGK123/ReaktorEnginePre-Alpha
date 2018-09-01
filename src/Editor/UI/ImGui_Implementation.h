#pragma once

//= INCLUDES ==================================
#include "../ImGui/imgui.h"
#include "Graphics/D3D11/D3D11GraphicsDevice.h"
//=============================================

struct SDL_Window;
union SDL_Event;

IMGUI_API bool	ImGui_Impl_Initialize(SDL_Window* window, Directus::Context* context);
IMGUI_API bool	ImGui_Impl_ProcessEvent(SDL_Event* event);
IMGUI_API void	ImGui_Impl_Shutdown();
IMGUI_API void	ImGui_Impl_NewFrame(SDL_Window* window);

// Use if you want to reset your rendering device without losing ImGui state.
IMGUI_API void	ImGui_Impl_InvalidateDeviceObjects();
IMGUI_API bool	ImGui_Impl_CreateDeviceObjects();
