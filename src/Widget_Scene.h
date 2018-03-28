#pragma once
//= INCLUDES ======
#include "Widget.h"
#include <memory>
//=================

namespace TmingEngine
{
	class GameObject
	{
	public :
		GameObject()
		{
		}

		~GameObject()
		{
		}
	};
}



class Widget_Scene : public Widget
{
public:
	Widget_Scene();
	void Initialize(TmingEngine::Context* context) override;
	void Update() override;

	static std::weak_ptr<TmingEngine::GameObject> GetSelectedGameObject() { return m_gameObjectSelected; }
	static void SetSelectedGameObject(std::weak_ptr<TmingEngine::GameObject> gameObject);

private:
	// Tree
	void Tree_Show();
	void OnTreeBegin();
	void OnTreeEnd();
	void Tree_AddGameObject(TmingEngine::GameObject* gameObject);
	void HandleClicking();
	void HandleDragDrop(TmingEngine::GameObject* gameObjPtr);

	// Misc
	void ContextMenu();
	void HandleKeyShortcuts();

	// Context menu actions
	void Action_GameObject_Delete(std::weak_ptr<TmingEngine::GameObject> gameObject);
	TmingEngine::GameObject* Action_GameObject_CreateEmpty();
	void Action_GameObject_CreateCube();
	void Action_GameObject_CreateQuad();
	void Action_GameObject_CreateSphere();
	void Action_GameObject_CreateCylinder();
	void Action_GameObject_CreateCone();
	void Action_GameObject_CreateCamera();
	void Action_GameObject_CreateLightDirectional();
	void Action_GameObject_CreateLightPoint();
	void Action_GameObject_CreateLightSpot();
	void Action_GameObject_CreateRigidBody();
	void Action_GameObject_CreateCollider();
	void Action_GameObject_CreateConstraint();
	void Action_GameObject_CreateAudioSource();
	void Action_GameObject_CreateAudioListener();

	static std::weak_ptr<TmingEngine::GameObject> m_gameObjectSelected;
};