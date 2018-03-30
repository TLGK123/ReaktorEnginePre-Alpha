
//= INCLUDES ===========================
#include "IComponent.h"
//#include "Skybox.h"
//#include "Script.h"
//#include "RigidBody.h"
//#include "MeshRenderer.h"
//#include "MeshFilter.h"
//#include "LineRenderer.h"
//#include "Constraint.h"
//#include "Collider.h"
//#include "Camera.h"
//#include "AudioSource.h"
//#include "AudioListener.h"
//#include "Light.h"
#include "Transform.h"
#include "../GameObject.h"
#include "../../Core/Context.h"
#include "../../Core/GUIDGenerator.h"
#include "../../FileSystem/FileSystem.h"
//======================================

//= NAMESPACES =====
using namespace std;
//==================

namespace TmingEngine
{
	IComponent::IComponent(Context* context, GameObject* gameObject, Transform* transform)
	{
		m_context = context;
		m_gameObject = gameObject;
		m_transform = transform;
		m_enabled = true;
		m_ID = GENERATE_GUID;
	}

	std::shared_ptr<GameObject> IComponent::GetGameObject_RefStrong()
	{
		return m_gameObject->GetSharedPtr();
	}

	const string& IComponent::GetGameObjectName()
	{
		if (!m_gameObject)
			return NOT_ASSIGNED;

		return m_gameObject->GetName();
	}

	template <typename T>
	ComponentType IComponent::ToComponentType()
	{
		if (typeid(T) == typeid(AudioListener))
			return ComponentType_AudioListener;

		if (typeid(T) == typeid(AudioSource))
			return ComponentType_AudioSource;

		if (typeid(T) == typeid(Camera))
			return ComponentType_Camera;

		if (typeid(T) == typeid(Collider))
			return ComponentType_Collider;

		if (typeid(T) == typeid(Constraint))
			return ComponentType_Constraint;

		if (typeid(T) == typeid(Light))
			return ComponentType_Light;

		if (typeid(T) == typeid(LineRenderer))
			return ComponentType_LineRenderer;

		if (typeid(T) == typeid(MeshFilter))
			return ComponentType_MeshFilter;

		if (typeid(T) == typeid(MeshRenderer))
			return ComponentType_MeshRenderer;

		if (typeid(T) == typeid(RigidBody))
			return ComponentType_RigidBody;

		if (typeid(T) == typeid(Script))
			return ComponentType_Script;

		if (typeid(T) == typeid(Skybox))
			return ComponentType_Skybox;

		if (typeid(T) == typeid(Transform))
			return ComponentType_Transform;

		return ComponentType_Unknown;
	}

#define INSTANTIATE(T) template ENGINE_CLASS ComponentType IComponent::ToComponentType<T>()
	// Explicit template instantiation
	//INSTANTIATE(AudioListener);
	//INSTANTIATE(AudioSource);
	//INSTANTIATE(Camera);
	//INSTANTIATE(Collider);
	//INSTANTIATE(Constraint);
	//INSTANTIATE(Light);
	//INSTANTIATE(LineRenderer);
	//INSTANTIATE(MeshFilter);
	//INSTANTIATE(MeshRenderer);
	//INSTANTIATE(RigidBody);
	//INSTANTIATE(Script);
	//INSTANTIATE(Skybox);
	INSTANTIATE(Transform);
}