#pragma once

//= INCLUDES =====================
#include <memory>
#include <string>
#include "../../Core/EngineDefs.h"
//================================

namespace TmingEngine
{
	class GameObject;
	class Transform;
	class Context;
	

	enum ComponentType : unsigned int
	{
		ComponentType_AudioListener,
		ComponentType_AudioSource,
		ComponentType_Camera,
		ComponentType_Collider,
		ComponentType_Constraint,
		ComponentType_Light,
		ComponentType_LineRenderer,
		ComponentType_MeshFilter,
		ComponentType_MeshRenderer,
		ComponentType_RigidBody,
		ComponentType_Script,
		ComponentType_Skybox,
		ComponentType_Transform,
		ComponentType_Unknown
	};

	class ENGINE_CLASS IComponent
	{
	public:
		IComponent(Context* context, GameObject* gameObject, Transform* transform);
		virtual ~IComponent() {}

		// Runs when the component gets added
		virtual void OnInitialize() {}

		// Runs every time the simulation starts
		virtual void OnStart() {}

		// Runs every time the simulation stops
		virtual void OnStop() {}

		// Runs when the component is removed
		virtual void OnRemove() {}

		// Runs every frame
		virtual void OnUpdate() {}

		// Runs when the GameObject is being saved
		virtual void Serialize(FileStream* stream) {}

		// Runs when the GameObject is being loaded
		virtual void Deserialize(FileStream* stream) {}

		//= PROPERTIES ========================================================================
		GameObject* GetGameObject_Ref() { return m_gameObject; }
		std::shared_ptr<GameObject> GetGameObject_RefStrong();
		std::weak_ptr<GameObject> GetGameObject_RefWeak() { return GetGameObject_RefStrong(); }
		Transform* GetTransform() { return m_transform; }
		Context* GetContext() { return m_context; }
		unsigned int GetID() { return m_ID; }
		void SetID(unsigned int id) { m_ID = id; }
		ComponentType GetType() { return m_type; }
		void SetType(ComponentType type) { m_type = type; }
		//=====================================================================================

		//= HELPER FUNCTIONS ==================
		const std::string& GetGameObjectName();

		template <typename T>
		static ComponentType ToComponentType();
		//=====================================

	protected:
		// The type of the component
		ComponentType m_type = ComponentType_Unknown;
		// The id of the component
		unsigned int m_ID = 0;
		// The state of the component
		bool m_enabled = false;
		// The owner of the component
		GameObject* m_gameObject = nullptr;
		// The transform of the component (always exists)
		Transform* m_transform = nullptr;
		// The context of the engine
		Context* m_context = nullptr;
	};
}