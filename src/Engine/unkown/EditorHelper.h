
//= INCLUDES ========================
#include <string>
#include "imgui.h"
#include "Core/Engine.h"
#include "Core/EventSystem.h"
#include "FileSystem/FileSystem.h"

//===================================

static const int BUFFER_TEXT_DEFAULT = 255;

// An icon shader resource pointer by thumbnail id
#define SHADER_RESOURCE(thumbnail)						ThumbnailProvider::Get().GetShaderResourceByThumbnail(thumbnail)
// An icon shader resource pointer by type 
#define SHADER_RESOURCE_BY_TYPE(type)					ThumbnailProvider::Get().GetShaderResourceByType(type)
// An thumbnail button by thumbnail
#define THUMBNAIL_BUTTON(thumbnail, size)				ImGui::ImageButton(SHADER_RESOURCE(thumbnail), ImVec2(size, size))
// An thumbnail button by enum
#define THUMBNAIL_BUTTON_BY_TYPE(type, size)			ImGui::ImageButton(SHADER_RESOURCE_BY_TYPE(type), ImVec2(size, size))
// An thumbnail button by enum, with a specific ID
#define THUMBNAIL_BUTTON_TYPE_UNIQUE_ID(id, type, size)	ThumbnailProvider::Get().ImageButton_enum_id(id, type, size)

// A thumbnail image
#define THUMBNAIL_IMAGE(thumbnail, size)								\
	ImGui::Image(														\
	ThumbnailProvider::Get().GetShaderResourceByThumbnail(thumbnail),	\
	ImVec2(size, size),													\
	ImVec2(0, 0),														\
	ImVec2(1, 1),														\
	ImColor(255, 255, 255, 255),										\
	ImColor(255, 255, 255, 0))											\

// A thumbnail image by shader resource
#define THUMBNAIL_IMAGE_BY_SHADER_RESOURCE(srv, size)	\
	ImGui::Image(										\
	srv,												\
	ImVec2(size, size),									\
	ImVec2(0, 0),										\
	ImVec2(1, 1),										\
	ImColor(255, 255, 255, 255),						\
	ImColor(255, 255, 255, 0))							\

// A thumbnail image by enum
#define THUMBNAIL_IMAGE_BY_ENUM(type, size)	\
	ImGui::Image(							\
	SHADER_RESOURCE_BY_TYPE(type),			\
	ImVec2(size, size),						\
	ImVec2(0, 0),							\
	ImVec2(1, 1),							\
	ImColor(255, 255, 255, 255),			\
	ImColor(255, 255, 255, 0))				\

//class EditorHelper
//{
//public:
//	EditorHelper()
//	{
//		m_context = nullptr;
//		m_engine = nullptr;
//		m_resourceManager = nullptr;
//		m_scene = nullptr;
//		m_isLoading = false;
//
//		SUBSCRIBE_TO_EVENT(EVENT_MODEL_LOADED, EVENT_HANDLER(ProgressDialog_Hide));
//		SUBSCRIBE_TO_EVENT(EVENT_SCENE_SAVED, EVENT_HANDLER(ProgressDialog_Hide));
//		SUBSCRIBE_TO_EVENT(EVENT_SCENE_LOADED, EVENT_HANDLER(ProgressDialog_Hide));
//	}
//	~EditorHelper() {}
//
//	static EditorHelper& Get()
//	{
//		static EditorHelper instance;
//		return instance;
//	}
//
//	void Initialize(TmingEngine::Context* context)
//	{
//		m_context = context;
//		m_engine = m_context->GetSubsystem<TmingEngine::Engine>();
//		m_resourceManager = m_context->GetSubsystem<TmingEngine::ResourceManager>();
//		m_scene = m_context->GetSubsystem<TmingEngine::Scene>();
//	}
//
//	void Update()
//	{
//		if (m_showProgressDialog)
//		{
//			ProgressDialog_Show();
//		}
//	}
//
//	std::weak_ptr<TmingEngine::Texture> GetOrLoadTexture(const std::string& filePath, bool async = false)
//	{
//		// Validate file path
//		if (TmingEngine::FileSystem::IsDirectory(filePath))
//			return std::weak_ptr<TmingEngine::Texture>();
//		if (!TmingEngine::FileSystem::IsSupportedImageFile(filePath) && !TmingEngine::FileSystem::IsEngineTextureFile(filePath))
//			return std::weak_ptr<TmingEngine::Texture>();
//
//		// Compute some useful information
//		auto path = TmingEngine::FileSystem::GetRelativeFilePath(filePath);
//		auto name = TmingEngine::FileSystem::GetFileNameNoExtensionFromFilePath(path);
//
//		// Check if this texture is already cached, if so return the cached one
//		auto resourceManager = m_context->GetSubsystem<TmingEngine::ResourceManager>();
//		if (auto cached = resourceManager->GetResourceByName<TmingEngine::Texture>(name).lock())
//		{
//			return cached;
//		}
//
//		// Since the texture is not cached, load it and returned a cached ref
//		auto texture = std::make_shared<TmingEngine::Texture>(m_context);
//		texture->SetResourceName(name);
//		texture->SetResourceFilePath(path);
//		if (!async)
//		{
//			texture->LoadFromFile(path);
//		}
//		else
//		{
//			m_context->GetSubsystem<TmingEngine::Threading>()->AddTask([texture, filePath]()
//			{
//				texture->LoadFromFile(filePath);
//			});
//		}
//
//		return texture->Cache<TmingEngine::Texture>();
//	}
//
//	void LoadModel(const std::string& filePath)
//	{
//		// Make the engine stop
//		SetEngineUpdate(false);
//		SetEngineLoading(true);
//
//		// Load the model asynchronously
//		m_context->GetSubsystem<TmingEngine::Threading>()->AddTask([this, filePath]()
//		{
//			m_resourceManager->Load<TmingEngine::Model>(filePath);
//		});
//		m_showProgressDialog = true;
//		m_isLoadingModel = true;
//	}
//
//	void LoadScene(const std::string& filePath)
//	{
//		// Make the engine stop
//		SetEngineUpdate(false);
//		SetEngineLoading(true);
//
//		// Load the scene asynchronously
//		m_context->GetSubsystem<TmingEngine::Threading>()->AddTask([this, filePath]()
//		{
//			m_scene->LoadFromFile(filePath);
//		});
//		m_showProgressDialog = true;
//		m_isLoadingModel = false;
//	}
//
//	void SaveScene(const std::string& filePath)
//	{
//		m_context->GetSubsystem<TmingEngine::Threading>()->AddTask([this, filePath]()
//		{
//			m_scene->SaveToFile(filePath);
//		});
//		m_showProgressDialog = true;
//		m_isLoadingModel = false;
//	}
//
//	// Whether the engine should update & render or not
//	void SetEngineUpdate(bool update)
//	{
//		auto flags = m_engine->EngineMode_GetAll();
//		flags = update ? flags | TmingEngine::Engine_Update : flags & ~TmingEngine::Engine_Update;
//		flags = update ? flags | TmingEngine::Engine_Render : flags & ~TmingEngine::Engine_Render;
//		m_engine->EngineMode_SetAll(flags);
//	}
//	// LOADING (Whether any editor system caused the engine to load something
//	void SetEngineLoading(bool loading) { m_isLoading = loading; }
//	bool GetEngineLoading() { return m_isLoading; }
//
//	static void SetCharArray(char* array, const std::string& value)
//	{
//		if (value.length() > BUFFER_TEXT_DEFAULT)
//			return;
//
//		memset(&array[0], 0, BUFFER_TEXT_DEFAULT * sizeof(array[0]));
//		copy(value.begin(), value.end(), array);
//	}
//
//	template <class T, class = typename std::enable_if<
//		std::is_same<T, int>::value ||
//		std::is_same<T, float>::value ||
//		std::is_same<T, bool>::value ||
//		std::is_same<T, double>::value
//	>::type>
//		static void SetCharArray(char* array, T value) { SetCharArray(array, std::to_string(value)); }
//
//	//= CONVERSIONS ===================================================================================================
//	static ImVec4 ToImVec4(const TmingEngine::Math::Vector4& v) { return ImVec4(v.x, v.y, v.z, v.w); }
//	static TmingEngine::Math::Vector4 ToVector4(const ImVec4& v) { return TmingEngine::Math::Vector4(v.x, v.y, v.z, v.w); }
//	static ImVec2 ToImVec2(const TmingEngine::Math::Vector2& v) { return ImVec2{ v.x,v.y }; }
//	static TmingEngine::Math::Vector2 ToVector2(const ImVec2& v) { return TmingEngine::Math::Vector2{ v.x,v.y }; }
//	//=================================================================================================================
//
//private:
//	void ProgressDialog_Show()
//	{
//		// Tick	
//		ProgressDialog::Get().SetIsVisible(m_showProgressDialog);
//		ProgressDialog::Get().Update();
//
//		// Show progress
//		if (m_isLoadingModel)
//		{
//			auto importer = m_resourceManager->GetModelImporter().lock();
//			ProgressDialog::Get().SetProgress(importer->GetProgress());
//			ProgressDialog::Get().SetProgressStatus(importer->GetProgressStatus());
//		}
//		else
//		{
//			ProgressDialog::Get().SetProgress(m_scene->GetProgress());
//			ProgressDialog::Get().SetProgressStatus(m_scene->GetProgressStatus());
//		}
//	}
//
//	void ProgressDialog_Hide()
//	{
//		m_showProgressDialog = false;
//		ProgressDialog::Get().SetIsVisible(false);
//		SetEngineUpdate(true);
//		SetEngineLoading(false);
//	}
//
//	TmingEngine::Context* m_context;
//	TmingEngine::Engine* m_engine;
//	TmingEngine::ResourceManager* m_resourceManager;
//	TmingEngine::Scene* m_scene;
//	bool m_isLoading;
//	bool m_showProgressDialog = false;
//	bool m_isLoadingModel = false;
//};