#pragma once

//= INCLUDES ===============
#include <map>
#include <vector>
#include <functional>
//#include "Variant.h"
//==========================

/*
HOW TO USE
=============================================================================
To subscribe a function to an event	-> SUBSCRIBE_TO_EVENT(EVENT_ID, Handler);
To fire an event					-> FIRE_EVENT(EVENT_ID);
To fire an event with data			-> FIRE_EVENT_DATA(EVENT_ID, Variant)
=============================================================================
*/

//= EVENTS ===============================================================================
#define EVENT_UPDATE			0	// Fired when the most engine subsystems should update
#define EVENT_RENDER			1	// Fired when the Renderer should start rendering
#define EVENT_SCENE_SAVED		2	// Fired when the Scene finished saving to file
#define EVENT_SCENE_LOADED		3	// Fired when the Scene finished loading from file
#define EVENT_SCENE_CLEARED		5	// Fired when the Scene should clear everything
#define EVENT_SCENE_RESOLVE		6	// Fired when the Scene should be resolved
#define EVENT_SCENE_RESOLVED	7	// Fired when the Scene has been resolved
#define EVENT_MODEL_LOADED		8	// Fired when the ModelImporter finished loading
//========================================================================================

//= MACROS ===============================================================================================
#define EVENT_HANDLER_STATIC(function)			[](TmingEngine::Variant var)		{ function(); }
#define EVENT_HANDLER(function)					[this](TmingEngine::Variant var)	{ function(); }
#define EVENT_HANDLER_VARIANT(function)			[this](TmingEngine::Variant var)	{ function(var); }
#define EVENT_HANDLER_VARIANT_STATIC(function)	[](TmingEngine::Variant var)		{ function(var); }
#define SUBSCRIBE_TO_EVENT(eventID, function)	TmingEngine::EventSystem::Get().Subscribe(eventID, function);
#define FIRE_EVENT(eventID)						TmingEngine::EventSystem::Get().Fire(eventID)
#define FIRE_EVENT_DATA(eventID, data)			TmingEngine::EventSystem::Get().Fire(eventID, data)
//========================================================================================================

namespace TmingEngine
{
	class ENGINE_CLASS EventSystem
	{
	public:
		static EventSystem& Get()
		{
			static EventSystem instance;
			return instance;
		}

	/*	typedef std::function<void(Variant)> subscriber;

		void Subscribe(int eventID, subscriber&& func)
		{
			m_subscribers[eventID].push_back(std::forward<subscriber>(func));
		}

		void Fire(int eventID, const Variant& data = 0)
		{
			if (m_subscribers.find(eventID) == m_subscribers.end())
				return;

			for (const auto& subscriber : m_subscribers[eventID])
			{
				subscriber(data);
			}
		}*/
		//void Clear() { m_subscribers.clear(); }

	private:
	//	std::map<uint8_t, std::vector<subscriber>> m_subscribers;
	};
}
