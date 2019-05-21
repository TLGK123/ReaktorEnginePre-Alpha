//= INCLUDES =================================
#include "Engine.h"
#include "Timer.h"
#include<memory>
#include "GameObject.hpp"
#include"Log/Log.h"
#include "../Scene/Scene.hpp"
//#include "Settings.h"
//#include "../Logging/Log.h"
//#include "../Threading/Threading.h"
//#include "../Resource/ResourceManager.h"
//#include "../Scripting/Scripting.h"
//#include "../Graphics/Renderer.h"
//#include "../Audio/Audio.h"
//#include "../Core/EngineBackends.h"
//#include "../Core/EventSystem.h"
//#include "../Input/DInput/DInput.h"
//#include "../Physics/Physics.h"
//#include "../Scene/Scene.h"
//#include "Stopwatch.h"
//#include "../Profiling/Profiler.h"
//===========================================

//= NAMESPACES =====
using namespace std;
//==================

namespace TmingEngine
{
	//void* Engine::m_drawHandle = nullptr;
	//void* Engine::m_windowHandle = nullptr;
	//void* Engine::m_windowInstance = nullptr;
	//unsigned long Engine::m_flags = 0;
	//static unique_ptr<Stopwatch> g_stopwatch;

	Engine::Engine(Context* context) : Subsystem(context)
	{
		//m_flags |= Engine_Update;
		//m_flags |= Engine_Render;
		//m_flags |= Engine_Physics;
		//m_flags |= Engine_Game;

		m_timer = nullptr;
		//g_stopwatch = make_unique<Stopwatch>();

		// Register self as a subsystem
		m_context->RegisterSubsystem(this);

		// Initialize global/static subsystems
		//Log::Initialize();
		//FileSystem::Initialize();
		//Settings::Get().Initialize();

		// Register subsystems
		m_context->RegisterSubsystem(new Timer(m_context));
		//m_context->RegisterSubsystem(new Input(m_context));
		//m_context->RegisterSubsystem(new Threading(m_context));
		//m_context->RegisterSubsystem(new ResourceManager(m_context));
		//m_context->RegisterSubsystem(new Graphics(m_context));
		//m_context->RegisterSubsystem(new Renderer(m_context));
		//m_context->RegisterSubsystem(new Audio(m_context));
		//m_context->RegisterSubsystem(new Physics(m_context));
		//m_context->RegisterSubsystem(new Scripting(m_context));
		//m_context->RegisterSubsystem(new Scene(m_context));
	}

	bool Engine::Initialize()
	{
		bool success = true;

		// Timer
		m_timer = m_context->GetSubsystem<Timer>();
		if (!m_timer->Initialize())
		{
			//Debug::Log("Failed to initialize Timer subsystem");
			success = false;
		}

        Scene start =  new Scene();
       GameObject * SceneRoot = new GameObject("Untiled");
        auto s = new GameObject();
 //      GameObject * ga = new GameObject("root");
//        auto isRoot =SceneRoot->transform->IsRoot();
//        ga->transform->SetParent(SceneRoot->transform) ;
//
//        Debug::Log("current is root %s \n" ,  isRoot?"true":"false" );
        
       // cout<< " current is root "<< isRoot << endl;
        
		//// Input
		//if (!m_context->GetSubsystem<Input>()->Initialize())
		//{
		//	LOG_ERROR("Failed to initialize Input subsystem");
		//	success = false;
		//}

		//// Threading
		//if (!m_context->GetSubsystem<Threading>()->Initialize())
		//{
		//	LOG_ERROR("Failed to initialize Multithreading subsystem");
		//	success = false;
		//}

		//// ResourceManager
		//if (!m_context->GetSubsystem<ResourceManager>()->Initialize())
		//{
		//	LOG_ERROR("Failed to initialize ResourceManager subsystem");
		//	success = false;
		//}

		//// Graphics
		//m_context->GetSubsystem<Graphics>()->SetHandle(m_drawHandle);
		//if (!m_context->GetSubsystem<Graphics>()->Initialize())
		//{
		//	LOG_ERROR("Failed to initialize Graphics subsystem");
		//	success = false;
		//}

		//// Renderer
		//if (!m_context->GetSubsystem<Renderer>()->Initialize())
		//{
		//	LOG_ERROR("Failed to initialize Renderer subsystem");
		//	success = false;
		//}

		//// Audio
		//if (!m_context->GetSubsystem<Audio>()->Initialize())
		//{
		//	LOG_ERROR("Failed to initialize Audio subsystem");
		//	success = false;
		//}

		//// Physics
		//if (!m_context->GetSubsystem<Physics>()->Initialize())
		//{
		//	LOG_ERROR("Failed to initialize Physics subsystem");
		//	success = false;
		//}

		//// Scripting
		//if (!m_context->GetSubsystem<Scripting>()->Initialize())
		//{
		//	LOG_ERROR("Failed to initialize Scripting subsystem");
		//	success = false;
		//}

		//// Scene
		//if (!m_context->GetSubsystem<Scene>()->Initialize())
		//{
		//	LOG_ERROR("Failed to initialize Scene subsystem");
		//	success = false;
		//}

		//Profiler::Get().Initialize(m_context);
		//g_stopwatch->Start();

        
        
        
		return success;
	}

	void Engine::Tick()
	{
		//= MAX FPS =============================================================
		//if (g_stopwatch->GetElapsedTimeSec() < 1.0 / Settings::Get().GetMaxFPS())
		//{
		//	return;
		//}
		//g_stopwatch->Start();
		////=======================================================================

		//// Timer always ticks
		m_timer->Tick();
		//Debug::Log("ÿ֡ʱ����: %f\n", m_timer->GetDeltaTimeMs());
		//if (EngineMode_IsSet(Engine_Update))
		//{
		//	FIRE_EVENT_DATA(EVENT_UPDATE, m_timer->GetDeltaTimeSec());
		//}

		//if (EngineMode_IsSet(Engine_Render))
		//{
		//	FIRE_EVENT(EVENT_RENDER);
		//}

		Update();
	}

	void Engine::Update()
	{
	}

	void Engine::Shutdown()
	{
		// The context will deallocate the subsystems
		// in the reverse order in which they were registered.
		//SafeDelete(m_context);

		// Release Log singleton
	   //Log::Release();
	}

	//void Engine::SetHandles(void* drawHandle, void* windowHandle, void* windowInstance)
	//{
	//	m_drawHandle = drawHandle;
	//	m_windowHandle = windowHandle;
	//	m_windowInstance = windowInstance;
	//}
}
