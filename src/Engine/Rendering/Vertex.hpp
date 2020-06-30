//  Vertex_h
//  TmingEngine
//

#ifndef Vertex_h
#define Vertex_h
#include "im.h"
#include "Core/Math/Vector3.h"
#include "Core/Math/Vector2.h"

namespace TmingEngine
{
	struct Vertex {
		Vector3 Position;

		Vector3 Normal;

		Vector2 TexCoords;

		Vector3 Tangent;

		Vector3 Bitangent;
	};
}

#endif /* Vertex_h */