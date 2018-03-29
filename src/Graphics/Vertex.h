#pragma once
//= INCLUDES ===============
#include "../Math/Vector2.h"
#include "../Math/Vector3.h"
#include "../Math/Vector4.h"
//==========================

namespace TmingEngine
{
	struct VertexPosTexTBN
	{
		Vector3 position;
		Vector2 uv;
		Vector3 normal;
		Vector3 tangent;
		Vector3 bitangent;

		VertexPosTexTBN() {}
		VertexPosTexTBN(
			const Vector3& position,
			const Vector2& uv,
			const Vector3& normal,
			const Vector3& tangent,
			const Vector3& bitangent)
		{
			this->position = position;
			this->uv = uv;
			this->normal = normal;
			this->tangent = tangent;
			this->bitangent = bitangent;
		}
	};

	struct VertexPosTexNor
	{
		Vector3 position;
		Vector2 uv;
		Vector3 normal;
	};

	struct VertexPosTex
	{
		VertexPosTex() {}
		VertexPosTex(const Vector3& position, const Vector2& uv)
		{
			this->position = position;
			this->uv = uv;
		}

		Vector3 position;
		Vector2 uv;
	};

	struct VertexPosCol
	{
		VertexPosCol() {}
		VertexPosCol(const Vector3& position, const Vector4& color)
		{
			this->position = position;
			this->color = color;
		}

		Vector3 position;
		Vector4 color;
	};
}