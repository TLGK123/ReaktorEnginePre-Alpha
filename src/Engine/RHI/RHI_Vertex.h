

#pragma once

//= INCLUDES ===============
#include "../Math/Vector2.h"
#include "../Math/Vector3.h"
#include "../Math/Vector4.h"
//==========================

namespace TmingEngine
{
	struct RHI_Vertex_PosUvNorTan
	{
		RHI_Vertex_PosUvNorTan(){}
		RHI_Vertex_PosUvNorTan(
			const Math::Vector3& position,
			const Math::Vector2& uv,
			const Math::Vector3& normal,
			const Math::Vector3& tangent)
		{
			this->pos[0]	= position.x;
			this->pos[1]	= position.y;
			this->pos[2]	= position.z;

			this->uv[0]		= uv.x;
			this->uv[1]		= uv.y;

			this->normal[0]	= normal.x;
			this->normal[1]	= normal.y;
			this->normal[2]	= normal.z;

			this->tangent[0]	= tangent.x;
			this->tangent[1]	= tangent.y;
			this->tangent[2]	= tangent.z;
		}

		float pos[3]		= { 0 };
		float uv[2]			= { 0 };
		float normal[3]		= { 0 };
		float tangent[3]	= { 0 };
	};

	struct RHI_Vertex_PosUvNor
	{
		RHI_Vertex_PosUvNor(){}
		RHI_Vertex_PosUvNor(const Math::Vector3& position, const Math::Vector2& uv, const Math::Vector3& normal)
		{
			this->pos[0] = position.x;
			this->pos[1] = position.y;
			this->pos[2] = position.z;

			this->uv[0] = uv.x;
			this->uv[1] = uv.y;

			this->normal[0] = normal.x;
			this->normal[1] = normal.y;
			this->normal[2] = normal.z;
		}

		float pos[3]	= { 0 };
		float uv[2]		= { 0 };
		float normal[3] = { 0 };
	};

	struct RHI_Vertex_PosUv
	{
		RHI_Vertex_PosUv(){}

		RHI_Vertex_PosUv(float posX, float posY, float posZ, float uvX, float uvY)
		{
			pos[0] = posX;
			pos[1] = posY;
			pos[2] = posZ;

			uv[0] = uvX;
			uv[1] = uvY;
		}

		RHI_Vertex_PosUv(const Math::Vector3& position, const Math::Vector2& uv)
		{
			this->pos[0]	= position.x;
			this->pos[1]	= position.y;
			this->pos[2]	= position.z;

			this->uv[0]		= uv.x;
			this->uv[1]		= uv.y;
		}

		float pos[3]		= { 0 };
		float uv[2]			= { 0 };
	};

	struct RHI_Vertex_PosCol
	{
		RHI_Vertex_PosCol(){}
		RHI_Vertex_PosCol(const Math::Vector3& position, const Math::Vector4& color)
		{
			this->pos[0]	= position.x;
			this->pos[1]	= position.y;
			this->pos[2]	= position.z;

			this->color[0]	= color.x;
			this->color[1]	= color.y;
			this->color[2]	= color.z;
			this->color[3]	= color.w;
		}

		float pos[3]	= {0};
		float color[4]	= {0};
	};

	static_assert(std::is_trivially_copyable<RHI_Vertex_PosUvNorTan>::value,	"RHI_Vertex_PosUVTBN is not trivially copyable");
	static_assert(std::is_trivially_copyable<RHI_Vertex_PosUvNor>::value,		"RHI_Vertex_PosUVNor is not trivially copyable");
	static_assert(std::is_trivially_copyable<RHI_Vertex_PosUv>::value,			"RHI_Vertex_PosUV is not trivially copyable");
	static_assert(std::is_trivially_copyable<RHI_Vertex_PosCol>::value,			"RHI_Vertex_PosCol is not trivially copyable");
}
