#pragma once

//= INCLUDES =======
#include "Context.h"
//==================

#define ENGINE_VERSION "v0.1 alpha"


namespace TmingEngine
{
	enum Engine_Mode : unsigned long
	{
		Engine_Update = 1UL << 0,	// Should the engine update?
		Engine_Physics = 1UL << 1, // Should physics update?	
		Engine_Render = 1UL << 2,	// Should the engine render?
		Engine_Game = 1UL << 3,	// Is the engine running in game or editor mode?
	};

	class Timer;

	class ENGINE_CLASS Engine : public Subsystem
	{
	public:
		Engine(Context* context);
		~Engine() { Shutdown(); }

		//= SUBSYSTEM =============
		bool Initialize() override;
		//=========================

		// Performs a complete simulation cycle
		void Tick();
		// Shuts down the engine
		void Shutdown();

		//= ENGINE MODE FLAGS  =====================================================================================================
		// Returns all engine mode flags
		static unsigned long EngineMode_GetAll() { return m_flags; }
		// Set's all engine mode flags
		static void EngineMode_SetAll(unsigned long flags) { m_flags = flags; }
		// Enables an engine mode flag
		static void EngineMode_Enable(Engine_Mode flag) { m_flags |= flag; }
		// Removes an engine mode flag
		static void EngineMode_Disable(Engine_Mode flag) { m_flags &= ~flag; }
		// Toggles an engine mode flag
		static void EngineMode_Toggle(Engine_Mode flag) { m_flags = !EngineMode_IsSet(flag) ? m_flags | flag : m_flags & ~flag; }
		// Returns whether engine mode flag is set
		static bool EngineMode_IsSet(Engine_Mode flag) { return m_flags & flag; }
		//==========================================================================================================================

		//= WINDOW ========================================================================
		static void SetHandles(void* drawHandle, void* windowHandle, void* windowInstance);
		static void* GetWindowHandle() { return m_windowHandle; }
		static void* GetWindowInstance() { return m_windowInstance; }
		//=================================================================================

		// Returns the engine's context
		Context* GetContext() { return m_context; }

	private:
		static void* m_drawHandle;
		static void* m_windowHandle;
		static void* m_windowInstance;
		static unsigned long m_flags;
		Timer* m_timer;
	};
}