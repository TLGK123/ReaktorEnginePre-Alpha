//
//#pragma once
//
////= INCLUDES ==================
//#include "MathHelper.h"
//#include "Vector3.h"
//#include <vector>
////#include "../Graphics/Vertex.h"
////=============================
//
//namespace TmingEngine
//{
//	class Mesh;
//	namespace Math
//	{
//		class Matrix;
//
//		class ENGINE_CLASS BoundingBox
//		{
//		public:
//			// Construct with zero size.
//			BoundingBox();
//
//			// Construct from minimum and maximum vectors.
//			BoundingBox(const Vector3& min, const Vector3& max);
//
//			~BoundingBox();
//
//			// Assign from bounding box
//			BoundingBox& operator =(const BoundingBox& rhs)
//			{
//				min = rhs.min;
//				max = rhs.max;
//				return *this;
//			}
//
//			// Compute bounding box from vertices
//		//	void ComputeFromVertices(const std::vector<VertexPosTexTBN>& vertices);
//
//			// Returns the center
//			Vector3 GetCenter() const { return (max + min) * 0.5f; }
//
//			// Returns the size
//			Vector3 GetSize() const { return max - min; }
//
//			// Returns extents
//			Vector3 GetExtents() const { return (max - min) * 0.5f; }
//
//			// Test if a point is inside
//			Intersection IsInside(const Vector3& point) const;
//
//			// Test if a bounding box is inside
//			Intersection IsInside(const BoundingBox& box) const;
//
//			// Returns a transformed bounding box
//			BoundingBox Transformed(const Matrix& transform);
//
//			// Merge with another bounding box
//			void Merge(const BoundingBox& box);
//
//			void Undefine() { min = Vector3::InfinityNeg; max = Vector3::Infinity; }
//			bool Defined() const { return min.x != INFINITY; }
//
//			Vector3 min;
//			Vector3 max;
//			static const BoundingBox Zero;
//		};
//	}
//}
