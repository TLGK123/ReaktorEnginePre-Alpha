#pragma once
#include <vector>
#include <memory>
#include "Core\Context.h"
#include "Widget.h"

struct SDL_Window;
union SDL_Event;

	class Editor
	{
	public:
		Editor();
		~Editor();

		void Initialize();
		void HandleEvent();
		void Update();
		void ShutDown();
		
	private :
		void DrawEditor();
		void ApplyStyle();

		std::vector<std::unique_ptr<Widget>> m_widgets;
		TmingEngine::Context* m_context;

	};


