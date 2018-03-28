
//= INCLUDES ====
#include <string>
#include <vector>
#include <memory>
//===============

enum Thumbnail_Type
{
	Thumbnail_Custom,
	Icon_Component_Options,
	Icon_Component_AudioListener,
	Icon_Component_AudioSource,
	Icon_Component_Camera,
	Icon_Component_Collider,
	Icon_Component_Light,
	Icon_Component_Material,
	Icon_Component_MeshCollider,
	Icon_Component_MeshFilter,
	Icon_Component_MeshRenderer,
	Icon_Component_RigidBody,
	Icon_Component_Script,
	Icon_Component_Transform,
	Icon_Console_Info,
	Icon_Console_Warning,
	Icon_Console_Error,
	Thumbnail_Folder,
	Thumbnail_File_Audio,
	Thumbnail_File_Scene,
	Thumbnail_File_Model,
	Thumbnail_File_Default,
	Icon_Button_Play
};

namespace TmingEngine
{
	class Context;
	class Texture;
}

struct Thumbnail
{
	Thumbnail() {}
	Thumbnail(Thumbnail_Type type, std::shared_ptr<TmingEngine::Texture> texture, const std::string& filePath)
	{
		this->type = type;
		this->texture = texture;
		this->filePath = filePath;
	}

	Thumbnail_Type type;
	std::shared_ptr<TmingEngine::Texture> texture;
	std::string filePath;
};

class ThumbnailProvider
{
public:
	ThumbnailProvider();
	~ThumbnailProvider();

	void Initialize(TmingEngine::Context* context);

	//= SHADER RESOURCE ===========================================
	void* GetShaderResourceByType(Thumbnail_Type type);
	void* GetShaderResourceByFilePath(const std::string& filePath);
	void* GetShaderResourceByThumbnail(const Thumbnail& thumbnail);
	//=============================================================

	//= ImGui::ImageButton =======================================================
	bool ImageButton_enum_id(const char* id, Thumbnail_Type iconEnum, float size);
	bool ImageButton_filepath(const std::string& filepath, float size);
	//============================================================================

	//= THUMBNAIL ==================================================================================================
	const Thumbnail& Thumbnail_Load(const std::string& filePath, Thumbnail_Type type = Thumbnail_Custom, int size = 100);
	//==============================================================================================================

	static ThumbnailProvider& Get()
	{
		static ThumbnailProvider instance;
		return instance;
	}

private:
	const Thumbnail& GetThumbnailByType(Thumbnail_Type type);
	std::vector<Thumbnail> m_thumbnails;
	TmingEngine::Context* m_context;

};