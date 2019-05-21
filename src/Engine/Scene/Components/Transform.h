
#pragma once

//= INCLUDES =====================
#include "IComponent.h"
#include <vector>
#include "../../Math/Vector3.h"
#include "../../Math/Quaternion.h"
#include "../../Math/Matrix.h"
#include "../../Core/GameObject.hpp"
//#include "../Scene.h"
//================================

namespace TmingEngine
{
	class ENGINE_CLASS Transform : public IComponent
	{
	public:
		Transform(Context* context, GameObject* gameObject, Transform* transform);
		~Transform();

		//= ICOMPONENT ===============================
		void OnInitialize() override;
		void Serialize(FileStream* stream) override;
		void Deserialize(FileStream* stream) override;
		//============================================

		void UpdateTransform();

		//= POSITION ============================================================
//        Math::Vector3 GetPosition() { return m_worldTransform.GetTranslation(); }
//        const Math::Vector3& GetPositionLocal() { return m_positionLocal; }
//        void SetPosition(const Math::Vector3& position);
//        void SetPositionLocal(const Math::Vector3& position);
		//=======================================================================

		//= ROTATION ============================================================
//        Math::Quaternion GetRotation() { return m_worldTransform.GetRotation(); }
//        const Math::Quaternion& GetRotationLocal() { return m_rotationLocal; }
//        void SetRotation(const Math::Quaternion& rotation);
//        void SetRotationLocal(const Math::Quaternion& rotation);
		//=======================================================================

		//= SCALE ======================================================
//        Math::Vector3 GetScale() { return m_worldTransform.GetScale(); }
//        const Math::Vector3& GetScaleLocal() { return m_scaleLocal; }
//        void SetScale(const Math::Vector3& scale);
//        void SetScaleLocal(const Math::Vector3& scale);
		//==============================================================

		//= TRANSLATION/ROTATION =======================
//        void Translate(const Math::Vector3& delta);
//        void Rotate(const Math::Quaternion& delta);
//        void RotateLocal(const Math::Quaternion& delta);
		//==============================================

		//= DIRECTIONS ============
		Math::Vector3 GetUp();
		Math::Vector3 GetForward();
		Math::Vector3 GetRight();
		//=========================

		//= HIERARCHY ==============================================================
        bool IsRoot() { return !HasParent(); }
        bool HasParent() { return m_parent; }
        void SetParent(Transform* parent);
//        void BecomeOrphan();
//        bool HasChildren() { return GetChildrenCount() > 0 ? true : false; }
//        void AddChild(Transform* child);
//        Transform* GetRoot() { return HasParent() ? GetParent()->GetRoot() : this; }
//        Transform* GetParent() { return m_parent; }
//        Transform* GetChildByIndex(int index);
//        Transform* GetChildByName(const std::string& name);
//        const std::vector<Transform*>& GetChildren() { return m_children; }
//        int GetChildrenCount() { return (int)m_children.size(); }
//        void ResolveChildrenRecursively();
//        bool IsDescendantOf(Transform* transform);
//        void GetDescendants(std::vector<Transform*>* descendants);
		//==========================================================================

		void LookAt(const Math::Vector3& v) { m_lookAt = v; }
		Math::Matrix& GetWorldTransform() { return m_worldTransform; }
		Math::Matrix& GetLocalTransform() { return m_localTransform; }
        std::vector<Transform*> m_children; // the children of this transform
     
	private:
		// local
		Math::Vector3 m_positionLocal;
		Math::Quaternion m_rotationLocal;
		Math::Vector3 m_scaleLocal;

		Math::Matrix m_worldTransform;
		Math::Matrix m_localTransform;
		Math::Vector3 m_lookAt;

		Transform* m_parent; // the parent of this transform


		//= HELPER FUNCTIONS ================================================================
		Math::Matrix GetParentTransformMatrix();
	};
}
