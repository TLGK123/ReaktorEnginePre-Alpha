#include "Widget_Scene.h"
#include "imgui.h"
#include "DragDrop.h"

namespace HierarchyStatics
{
	//static GameObject* g_hoveredGameObject = nullptr;
	//static Engine* g_engine = nullptr;
	//static Scene* g_scene = nullptr;
	//static Input* g_input = nullptr;
	//static DragDropPayload g_payload;
}

Widget_Scene::Widget_Scene()
{
	m_title = "Scene";
	m_context = nullptr;
	// HierarchyStatics::g_scene = nullptr;  引擎的scene类的引用
}

void Widget_Scene::Initialize(TmingEngine::Context * context)
{
	Widget::Initialize(context);//调用父类的初始化方法

	//HierarchyStatics::g_engine = m_context->GetSubsystem<Engine>(); //获取引擎对象
	//HierarchyStatics::g_scene = m_context->GetSubsystem<Scene>();   //获取scene对象
	//HierarchyStatics::g_input = m_context->GetSubsystem<Input>();   //获取输入对象

	m_windowFlags |= ImGuiWindowFlags_HorizontalScrollbar;
}

void Widget_Scene::Update()
{
	// 编辑器帮助类，发现有东西在加载，不显示在层级管理中
	//if (EditorHelper::Get().GetEngineLoading())
	//	return;

	Tree_Show();
}

void Widget_Scene::SetSelectedGameObject(std::weak_ptr<TmingEngine::GameObject> gameObject)
{
}

void Widget_Scene::Tree_Show()
{
	//OnTreeBegin();
	if (ImGui::TreeNodeEx("Root", ImGuiTreeNodeFlags_DefaultOpen))
	{
		// Dropping on the scene node should unparent the GameObject
		//if (auto payload = DragDrop::Get().GetPayload(DragPayload_GameObject))
		//{
		//	auto gameObjectID = get<unsigned int>(payload->data);
		//	if (auto droppedGameObj = HierarchyStatics::g_scene->GetGameObjectByID(gameObjectID).lock())
		//	{
		//		droppedGameObj->GetTransformRef()->SetParent(nullptr);
		//	}
		//}

		//auto rootGameObjects = HierarchyStatics::g_scene->GetRootGameObjects();
		//for (const auto& gameObject : rootGameObjects)
		//{
		//	Tree_AddGameObject(gameObject.lock().get());
		//}
		ImGui::TreePop();
	}
	//OnTreeEnd();
}

void Widget_Scene::OnTreeBegin()
{
}

void Widget_Scene::OnTreeEnd()
{
}

void Widget_Scene::Tree_AddGameObject(TmingEngine::GameObject * gameObject)
{
}

void Widget_Scene::HandleClicking()
{
}

void Widget_Scene::HandleDragDrop(TmingEngine::GameObject * gameObjPtr)
{
}

void Widget_Scene::ContextMenu()
{
}

void Widget_Scene::HandleKeyShortcuts()
{
}

void Widget_Scene::Action_GameObject_Delete(std::weak_ptr<TmingEngine::GameObject> gameObject)
{
}

TmingEngine::GameObject * Widget_Scene::Action_GameObject_CreateEmpty()
{
	return nullptr;
}

void Widget_Scene::Action_GameObject_CreateCube()
{
}

void Widget_Scene::Action_GameObject_CreateQuad()
{
}

void Widget_Scene::Action_GameObject_CreateSphere()
{
}

void Widget_Scene::Action_GameObject_CreateCylinder()
{
}

void Widget_Scene::Action_GameObject_CreateCone()
{
}

void Widget_Scene::Action_GameObject_CreateCamera()
{
}

void Widget_Scene::Action_GameObject_CreateLightDirectional()
{
}

void Widget_Scene::Action_GameObject_CreateLightPoint()
{
}

void Widget_Scene::Action_GameObject_CreateLightSpot()
{
}

void Widget_Scene::Action_GameObject_CreateRigidBody()
{
}

void Widget_Scene::Action_GameObject_CreateCollider()
{
}

void Widget_Scene::Action_GameObject_CreateConstraint()
{
}

void Widget_Scene::Action_GameObject_CreateAudioSource()
{
}

void Widget_Scene::Action_GameObject_CreateAudioListener()
{
}
