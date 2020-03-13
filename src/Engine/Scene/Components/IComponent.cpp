/*
Copyright(c) 2016-2019 Panos Karabelas

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and / or sell
copies of the Software, and to permit persons to whom the Software is furnished
to do so, subject to the following conditions :

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS
FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.IN NO EVENT SHALL THE AUTHORS OR
COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER
IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/

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
//#include "Transform.h"
//#include "../GameObject.h"
#include "../../Core/Context.h"
//#include "../../Core/GUIDGenerator.h"
//#include "../../FileSystem/FileSystem.h"
//======================================

//= NAMESPACES =====
using namespace std;
//==================

namespace TmingEngine
{
	IComponent::IComponent(Context* context, GameObject* gameObject, Transform* transform)
	{
		m_context		= context;
		m_gameObject	= gameObject;
		m_transform		= transform;
		m_enabled		= true;
	/*	m_ID			= GENERATE_GUID;*/
	}

	std::shared_ptr<GameObject> IComponent::GetGameObject_RefStrong()
	{
		return nullptr;
	//	return m_gameObject->GetSharedPtr();
	}

	const string& IComponent::GetGameObjectName()
	{
		if (!m_gameObject)
			return "NOT_ASSIGNED";

	 //  return m_gameObject->GetGameObjectName();
	}

	template <typename T>
	ComponentType IComponent::ToComponentType()
	{
//        if (typeid(T) == typeid(AudioListener))
//            return ComponentType_AudioListener;
//
//        if (typeid(T) == typeid(AudioSource))
//            return ComponentType_AudioSource;
//
//        if (typeid(T) == typeid(Camera))
//            return ComponentType_Camera;
//
//        if (typeid(T) == typeid(Collider))
//            return ComponentType_Collider;
//
//        if (typeid(T) == typeid(Constraint))
//            return ComponentType_Constraint;
//
//        if (typeid(T) == typeid(Light))
//            return ComponentType_Light;
//
//        if (typeid(T) == typeid(LineRenderer))
//            return ComponentType_LineRenderer;
//
//        if (typeid(T) == typeid(MeshFilter))
//            return ComponentType_MeshFilter;
//
//        if (typeid(T) == typeid(MeshRenderer))
//            return ComponentType_MeshRenderer;
//
//        if (typeid(T) == typeid(RigidBody))
//            return ComponentType_RigidBody;
//
//        if (typeid(T) == typeid(Script))
//            return ComponentType_Script;
//
//        if (typeid(T) == typeid(Skybox))
//            return ComponentType_Skybox;
//
//        if (typeid(T) == typeid(Transform))
//            return ComponentType_Transform;

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
	//INSTANTIATE(Transform);
}
