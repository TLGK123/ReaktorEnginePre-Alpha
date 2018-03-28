
//= INCLUDES =================
#include "imgui.h"
#include "EditorHelper.h"
#include "ThumbnailProvider.h"
#include <variant>
//============================

enum DragPayloadType
{
	DragPayload_Unknown,
	DragPayload_Texture,
	DragPayload_GameObject,
	DragPayload_Model,
	DragPayload_Audio,
	DragPayload_Script
};

struct DragDropPayload
{
	typedef std::variant<const char*, std::string, unsigned int> payloadVariant;
	DragDropPayload(DragPayloadType type = DragPayload_Unknown, payloadVariant data = nullptr)
	{
		this->type = type;
		this->data = data;
	}
	DragPayloadType type;
	payloadVariant data;
};

static bool g_isDragging = false;

class DragDrop
{
public:

	static DragDrop& Get()
	{
		static DragDrop instance;
		return instance;
	}

	bool DragBegin() { return ImGui::BeginDragDropSource(); }
	void DragPayload(const DragDropPayload& payload, void* thumbnailShaderResource = nullptr)
	{
		ImGui::SetDragDropPayload((const char*)&payload.type, (void*)&payload, sizeof(payload), ImGuiCond_Once);
		if (thumbnailShaderResource)
		{
			THUMBNAIL_IMAGE_BY_SHADER_RESOURCE(thumbnailShaderResource, 50);
		}
		else
		{
			THUMBNAIL_IMAGE_BY_ENUM(Thumbnail_File_Default, 50);
		}
	}
	void DragEnd() { ImGui::EndDragDropSource(); }

	DragDropPayload* GetPayload(DragPayloadType type)
	{
		if (ImGui::BeginDragDropTarget())
		{
			if (const ImGuiPayload* imguiPayload = ImGui::AcceptDragDropPayload((const char*)&type))
			{
				return (DragDropPayload*)imguiPayload->Data;
			}
			ImGui::EndDragDropTarget();
		}

		return nullptr;
	}
};