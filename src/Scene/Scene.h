#pragma once

//= INCLUDES ======================
#include <vector>
#include "../Math/Vector3.h"
#include "../Threading/Threading.h"
//=================================

namespace TmingEngine
{
	class GameObject;
	class Light;

	class ENGINE_CLASS Scene : public Subsystem
	{
	public:
		Scene(Context* context);
		~Scene();

		//= Subsystem =============
		bool Initialize() override;
		//=========================

		//= GameObject events ==========================
		// Runs every time the simulation starts
		void Start();
		// Runs every time the simulation stops
		void Stop();
		// Runs every frame
		void Update();
		// Runs when all GameObjects should be destroyed
		void Clear();
		//==============================================

		//= IO ========================================
		bool SaveToFile(const std::string& filePath);
		bool LoadFromFile(const std::string& filePath);
		//=============================================

		//= GAMEOBJECT HELPER FUNCTIONS =============================================================
		std::weak_ptr<GameObject> GameObject_CreateAdd();
		void GameObject_Add(std::shared_ptr<GameObject> gameObject);
		bool GameObject_Exists(std::weak_ptr<GameObject> gameObject);
		void GameObject_Remove(std::weak_ptr<GameObject> gameObject);
		const std::vector<std::shared_ptr<GameObject>>& GetAllGameObjects() { return m_gameObjects; }
		std::vector<std::weak_ptr<GameObject>> GetRootGameObjects();
		std::weak_ptr<GameObject> GetGameObjectRoot(std::weak_ptr<GameObject> gameObject);
		std::weak_ptr<GameObject> GetGameObjectByName(const std::string& name);
		std::weak_ptr<GameObject> GetGameObjectByID(unsigned int ID);
		int GetGameObjectCount() { return (int)m_gameObjects.size(); }
		//===========================================================================================

		//= SCENE RESOLUTION  ==============================
		void Resolve();
		const std::vector<std::weak_ptr<GameObject>>& GetRenderables() { return m_renderables; }
		std::weak_ptr<GameObject> GetMainCamera() { return m_mainCamera; }

		//= MISC =======================================
		void SetAmbientLight(float x, float y, float z);
		Vector3 GetAmbientLight();

		//= STATS ==============================================
		float GetFPS() { return m_fps; }
		const std::string& GetProgressStatus() { return m_progressStatus; }
		float GetProgress() { return m_jobsDone / m_jobsTotal; }
		bool IsLoading() { return m_isLoading; }

	private:
		//= COMMON GAMEOBJECT CREATION ====================
		std::weak_ptr<GameObject> CreateSkybox();
		std::weak_ptr<GameObject> CreateCamera();
		std::weak_ptr<GameObject> CreateDirectionalLight();
		//=================================================

		//= HELPER FUNCTIONS ======
		void ClearProgressStatus();
		void ComputeFPS();
		//========================

		std::vector<std::shared_ptr<GameObject>> m_gameObjects;
		std::vector<std::weak_ptr<GameObject>> m_renderables;

		std::weak_ptr<GameObject> m_mainCamera;
		std::weak_ptr<GameObject> m_skybox;
		Vector3 m_ambientLight;

		//= STATS ===================
		float m_fps;
		float m_timePassed;
		int m_frameCount;
		std::string m_progressStatus;
		float m_jobsDone;
		float m_jobsTotal;
		bool m_isLoading;
		bool m_isInEditorMode;
		//===========================
	};
}