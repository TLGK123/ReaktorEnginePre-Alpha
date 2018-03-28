#include "ThumbnailProvider.h"

ThumbnailProvider::ThumbnailProvider()
{
}

ThumbnailProvider::~ThumbnailProvider()
{
}

void ThumbnailProvider::Initialize(TmingEngine::Context * context)
{
}

void * ThumbnailProvider::GetShaderResourceByType(Thumbnail_Type type)
{
	return nullptr;
}

void * ThumbnailProvider::GetShaderResourceByFilePath(const std::string & filePath)
{
	return nullptr;
}

void * ThumbnailProvider::GetShaderResourceByThumbnail(const Thumbnail & thumbnail)
{
	return nullptr;
}

bool ThumbnailProvider::ImageButton_enum_id(const char * id, Thumbnail_Type iconEnum, float size)
{
	return false;
}

bool ThumbnailProvider::ImageButton_filepath(const std::string & filepath, float size)
{
	return false;
}

const Thumbnail & ThumbnailProvider::Thumbnail_Load(const std::string & filePath, Thumbnail_Type type, int size)
{
	// TODO: 在此处插入 return 语句
	Thumbnail t;
	return t;
}

const Thumbnail & ThumbnailProvider::GetThumbnailByType(Thumbnail_Type type)
{
	// TODO: 在此处插入 return 语句
	Thumbnail t;
	return t;
}
