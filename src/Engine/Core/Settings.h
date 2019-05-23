
#pragma once

//= INCLUDES ===============
#include "EngineDefs.h"
#include "../Math/Vector2.h"
#include "../Math/Vector4.h"
//==========================

namespace TmingEngine
{
	enum FPS_Policy
	{
		Fps_Unlocked,
		Fps_Fixed,
		Fps_FixedMonitor
	};

	class ENGINE_CLASS Settings
	{
	public:
		static Settings& Get()
		{
			static Settings instance;
			return instance;
		}

		Settings();
		~Settings() { Save(); }

		void Initialize();

		//= WINDOW ============================================================================================================
		void SetHandles(void* draw_handle, void* window_handle, void* window_instance, float window_width, float window_height)
		{
			m_draw_handle		= draw_handle;
			m_window_handle		= window_handle;
			m_windowInstance	= window_instance;
			m_window_size.x		= window_width;
			m_window_size.y		= window_height;
		}
		auto GetWindowHandle() const	{ return m_window_handle; }
		auto GetWindowInstance() const	{ return m_windowInstance; }
		//=====================================================================================================================

		//= FPS ============================================
		void SetFpsLimit(float fps);
		auto GetFpsLimit() const	{ return m_fps_limit; }
		auto GetFpsTarget() const	{ return m_fps_target; }
		auto GetFpsPolicy() const	{ return m_fps_policy; }
		//==================================================

		//= MISC ==============================================================
		auto GetIsFullScreen() const		{ return m_is_fullscreen; }
		auto GetIsMouseVisible() const		{ return m_is_mouse_visible; }
		auto GetShadowResolution() const	{ return m_shadow_map_resolution; }
		auto GetAnisotropy() const			{ return m_anisotropy; }
		auto GetMaxThreadCount() const		{ return m_max_thread_count; }	
		auto GetReverseZ() const			{ return m_reverse_z; }
		//=====================================================================

		// Third party lib versions
		std::string m_versionAngelScript;
		std::string m_versionAssimp;
		std::string m_versionBullet;
		std::string m_versionFMOD;
		std::string m_versionFreeImage;
		std::string m_versionFreeType;
		std::string m_versionImGui;
		std::string m_versionPugiXML = "1.90";
		std::string m_versionGraphicsAPI;

	private:
		void Save() const;
		void Load();

		void* m_draw_handle						= nullptr;
		void* m_window_handle					= nullptr;
		void* m_windowInstance					= nullptr;
		Math::Vector2 m_window_size				= Math::Vector2::Zero;
		bool m_is_fullscreen					= false;
		bool m_is_mouse_visible					= true;
		uint32_t m_shadow_map_resolution	= 4096;
		uint32_t m_anisotropy				= 16;
		uint32_t m_max_thread_count			= 0;
		float m_fps_limit						= 0.0f;
		float m_fps_target						= 165.0f;
		FPS_Policy m_fps_policy					= Fps_FixedMonitor;
		bool m_reverse_z						= true;
	};
}
