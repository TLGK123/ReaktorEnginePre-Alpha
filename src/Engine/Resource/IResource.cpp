
//= INCLUDES ===========================================
#include "../Resource/IResource.h"
//#include "ResourceManager.h"
//#include "../Font/Font.h"
//#include "../Audio/AudioClip.h"
//#include "../Graphics/Texture.h"
//#include "../Graphics/Animation.h"
//#include "../Graphics/Model.h"
//#include "../Graphics/Material.h"
//#include "../Graphics/Mesh.h"
//#include "../Graphics/DeferredShaders/ShaderVariation.h"
//======================================================

//= NAMESPACES ==========
using namespace std;
using namespace TmingEngine;
//=======================

string IResource::GetResourceFileName()
{
	return FileSystem::GetFileNameNoExtensionFromFilePath(m_resourceFilePath);
}

string IResource::GetResourceDirectory()
{
	return FileSystem::GetDirectoryFromFilePath(m_resourceFilePath);
}

template <typename T>
void IResource::RegisterResource()
{
	m_resourceType = DeduceResourceType<T>();
	m_resourceID = GENERATE_GUID;
	m_loadState = LoadState_Idle;
}

template <typename T>
bool IResource::IsCached()
{
	if (!m_context)
	{
		LOG_ERROR(string(typeid(T).name()) + "::IsCached(): Context is null, can't execute function");
		return weak_ptr<T>();
	}

	auto resourceManager = m_context->GetSubsystem<ResourceManager>();
	auto resource = resourceManager->GetResourceByName<T>(GetResourceName());
	return !resource.expired();
}

template <typename T>
weak_ptr<T> IResource::Cache()
{
	if (!m_context)
	{
		LOG_ERROR(string(typeid(T).name()) + "::Cache(): Context is null, can't execute function");
		return weak_ptr<T>();
	}

	auto resourceManager = m_context->GetSubsystem<ResourceManager>();
	auto resource = resourceManager->GetResourceByName<T>(GetResourceName());
	if (resource.expired())
	{
		return resourceManager->Add<T>(GetSharedPtr());
	}

	return resource;
}

string IResource::GetResourceTypeStr()
{
	//if (typeid(*this) == typeid(Texture))
	//	return "Texture";

	//if (typeid(*this) == typeid(AudioClip))
	//	return "Audio";

	//if (typeid(*this) == typeid(Material))
	//	return "Material";

	//if (typeid(*this) == typeid(ShaderVariation))
	//	return "ShaderVariation";

	//if (typeid(*this) == typeid(Mesh))
	//	return "Mesh";

	//if (typeid(*this) == typeid(Model))
	//	return "Model";

	//if (typeid(*this) == typeid(Animation))
	//	return "Animation";

	//if (typeid(*this) == typeid(Font))
	//	return "Font";

	return NOT_ASSIGNED;
}

ResourceType IResource::DeduceResourceType()
{
	//if (typeid(*this) == typeid(Texture))
	//	return Resource_Texture;

	//if (typeid(*this) == typeid(AudioClip))
	//	return Resource_Audio;

	//if (typeid(*this) == typeid(Material))
	//	return Resource_Material;

	//if (typeid(*this) == typeid(ShaderVariation))
	//	return Resource_Shader;

	//if (typeid(*this) == typeid(Mesh))
	//	return Resource_Mesh;

	//if (typeid(*this) == typeid(Model))
	//	return Resource_Model;

	//if (typeid(*this) == typeid(Animation))
	//	return Resource_Animation;

	//if (typeid(*this) == typeid(Font))
	//	return Resource_Font;

	return Resource_Unknown;
}

template <typename T>
ResourceType IResource::DeduceResourceType()
{
	if (typeid(T) == typeid(Texture))
		return Resource_Texture;

	if (typeid(T) == typeid(AudioClip))
		return Resource_Audio;

	if (typeid(T) == typeid(Material))
		return Resource_Material;

	if (typeid(T) == typeid(ShaderVariation))
		return Resource_Shader;

	if (typeid(T) == typeid(Mesh))
		return Resource_Mesh;

	if (typeid(T) == typeid(Model))
		return Resource_Model;

	if (typeid(T) == typeid(Animation))
		return Resource_Animation;

	if (typeid(T) == typeid(Font))
		return Resource_Font;

	return Resource_Unknown;
}

//// Explicit template instantiation
//#define INSTANTIATE_RegisterResource(T) template ENGINE_CLASS void IResource::RegisterResource<T>()
//INSTANTIATE_RegisterResource(Texture);
//INSTANTIATE_RegisterResource(AudioClip);
//INSTANTIATE_RegisterResource(Material);
//INSTANTIATE_RegisterResource(ShaderVariation);
//INSTANTIATE_RegisterResource(Mesh);
//INSTANTIATE_RegisterResource(Model);
//INSTANTIATE_RegisterResource(Animation);
//INSTANTIATE_RegisterResource(Font);
//
//// Explicit template instantiation
//#define INSTANTIATE_ToResourceType(T) template ENGINE_CLASS ResourceType IResource::DeduceResourceType<T>()
//INSTANTIATE_ToResourceType(Texture);
//INSTANTIATE_ToResourceType(AudioClip);
//INSTANTIATE_ToResourceType(Material);
//INSTANTIATE_ToResourceType(ShaderVariation);
//INSTANTIATE_ToResourceType(Mesh);
//INSTANTIATE_ToResourceType(Model);
//INSTANTIATE_ToResourceType(Animation);
//INSTANTIATE_ToResourceType(Font);
//
//// Explicit template instantiation
//#define INSTANTIATE_Cache(T) template ENGINE_CLASS weak_ptr<T> IResource::Cache<T>()
//INSTANTIATE_Cache(Texture);
//INSTANTIATE_Cache(AudioClip);
//INSTANTIATE_Cache(Material);
//INSTANTIATE_Cache(ShaderVariation);
//INSTANTIATE_Cache(Mesh);
//INSTANTIATE_Cache(Model);
//INSTANTIATE_Cache(Animation);
//INSTANTIATE_Cache(Font);