
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
//        Vector3 GetPosition() { return m_worldTransform.GetTranslation(); }
        const Vector3& GetPositionLocal() {
            return m_positionLocal;
        }
//       void SetPosition(const Vector3& position);
       void SetPositionLocal(const Vector3& position);
		//=======================================================================

		//= ROTATION ============================================================
//        Quaternion GetRotation() { return m_worldTransform.GetRotation(); }
//        const Quaternion& GetRotationLocal() { return m_rotationLocal; }
//        void SetRotation(const Quaternion& rotation);
//        void SetRotationLocal(const Quaternion& rotation);
		//=======================================================================

		//= SCALE ======================================================
//        Vector3 GetScale() { return m_worldTransform.GetScale(); }
//        const Vector3& GetScaleLocal() { return m_scaleLocal; }
//        void SetScale(const Vector3& scale);
//        void SetScaleLocal(const Vector3& scale);
		//==============================================================

		//= TRANSLATION/ROTATION =======================
//        void Translate(const Vector3& delta);
//        void Rotate(const Quaternion& delta);
//        void RotateLocal(const Quaternion& delta);
		//==============================================

		//= DIRECTIONS ============
		Vector3 GetUp();
		Vector3 GetForward();
		Vector3 GetRight();
		//=========================

		//= HIERARCHY ==============================================================
        bool IsRoot() { return !HasParent(); }
        bool HasParent() { return m_parent; }
        void SetParent(Transform* parent);
        GameObject * GetGameObject() {return m_gameObject; }
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

		void LookAt(const Vector3& v) { m_lookAt = v; }
		Matrix& GetWorldTransform() { return m_worldTransform; }
		Matrix& GetLocalTransform() { return m_localTransform; }
        std::vector<Transform*> m_children; // the children of this transform
     
	private:
		// local
		Vector3 m_positionLocal;
		Quaternion m_rotationLocal;
		Vector3 m_scaleLocal;

		Matrix m_worldTransform;
		Matrix m_localTransform;
		Vector3 m_lookAt;

		Transform* m_parent; // the parent of this transform


		//= HELPER FUNCTIONS ================================================================
		Matrix GetParentTransformMatrix();
	};
}
