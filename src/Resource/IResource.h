
#pragma once

//= INCLUDES ========================
#include "../Core/Context.h"
#include "../FileSystem/FileSystem.h"
#include "../Core/GUIDGenerator.h"
#include <memory>
//===================================

namespace TmingEngine
{
	enum ResourceType
	{
		Resource_Unknown,
		Resource_Texture,
		Resource_Audio,
		Resource_Material,
		Resource_Shader,
		Resource_Mesh,
		Resource_Model,
		Resource_Cubemap,
		Resource_Script, // not an actual resource, resource manager simply uses this to return standard resource path (must remove)
		Resource_Animation,
		Resource_Font
	};

	enum LoadState
	{
		LoadState_Idle,
		LoadState_Started,
		LoadState_Completed,
		LoadState_Failed
	};

	class ENGINE_CLASS IResource : public std::enable_shared_from_this<IResource>
	{
	public:
		IResource(Context* context)
		{
			m_context = context;
		}
		virtual ~IResource() {}

		template <typename T>
		void RegisterResource();

		//= PROPERTIES =========================================================================
		unsigned int GetResourceID() { return m_resourceID; }

		ResourceType GetResourceType() { return m_resourceType; }
		void SetResourceType(ResourceType type) { m_resourceType = type; }

		const std::string& GetResourceName() { return m_resourceName; }
		void SetResourceName(const std::string& name) { m_resourceName = name; }

		const std::string& GetResourceFilePath() { return m_resourceFilePath; }
		void SetResourceFilePath(const std::string& filePath) { m_resourceFilePath = filePath; }

		bool HasFilePath() { return m_resourceFilePath != NOT_ASSIGNED; }

		std::string GetResourceFileName();
		std::string GetResourceDirectory();
		//======================================================================================

		//= CACHE ================================================================
		// Checks whether the resource is cached or not
		template <typename T>
		bool IsCached();

		// Adds the resource into the resource cache and returns a cache reference
		// In case the resource is already cached, it returns the existing one
		template <typename T>
		std::weak_ptr<T> Cache();
		//========================================================================

		//= IO ================================================================
		virtual bool SaveToFile(const std::string& filePath) { return true; }
		virtual bool LoadFromFile(const std::string& filePath) { return true; }
		virtual unsigned int GetMemory() { return 0; }
		//=====================================================================

		//= TYPE ================================
		std::string GetResourceTypeStr();

		ResourceType DeduceResourceType();
		template <typename T>
		static ResourceType DeduceResourceType();
		//=======================================

		//= PTR ==========================================
		auto GetSharedPtr() { return shared_from_this(); }
		//================================================

		LoadState GetLoadState() { return m_loadState; }
		void GetLoadState(LoadState state) { m_loadState = state; }

	protected:
		unsigned int m_resourceID = NOT_ASSIGNED_HASH;
		std::string m_resourceName = NOT_ASSIGNED;
		std::string m_resourceFilePath = NOT_ASSIGNED;
		ResourceType m_resourceType = Resource_Unknown;
		LoadState m_loadState = LoadState_Idle;
		Context* m_context = nullptr;
	};
}
