//
////= INCLUDES ==============
//#include "Quaternion.h"
//#include "MathHelper.h"
//#include "../Math/Matrix.h"
////=========================
//
////= NAMESPACES =====
//using namespace std;
////==================
//
////= Based on ==========================================================================//
//// http://www.euclideanspace.com/maths/algebra/realNormedAlgebra/quaternions/index.htm //
//// Heading	-> Yaw		-> Y-axis													   //
//// Attitude	-> Pitch	-> X-axis													   //
//// Bank		-> Roll		-> Z-axis													   //
////=====================================================================================//
//
//namespace TmingEngine::Math
//{
//	const Quaternion Quaternion::Identity(0.0f, 0.0f, 0.0f, 1.0f);
//
//	//= FROM ==================================================================================
//	void Quaternion::FromAxes(const Vector3& xAxis, const Vector3& yAxis, const Vector3& zAxis)
//	{
//		*this = Matrix(
//			xAxis.x, yAxis.x, zAxis.x, 0.0f,
//			xAxis.y, yAxis.y, zAxis.y, 0.0f,
//			xAxis.z, yAxis.z, zAxis.z, 0.0f,
//			0.0f, 0.0f, 0.0f, 1.0f
//		).GetRotation();
//	}
//	//========================================================================================
//
//	Quaternion Quaternion::Inverse(const Quaternion& q)
//	{
//		float lenSquared = q.LengthSquared();
//
//		if (lenSquared == 1.0f)
//			return q.Conjugate();
//
//		if (lenSquared >= M_EPSILON)
//			return q.Conjugate() * (1.0f / lenSquared);
//
//		// impemented this here because Identity (static)
//		// doesnt play well with dllexport
//		return Quaternion(0, 0, 0, 1);
//	}
//
//	string Quaternion::ToString() const
//	{
//		char tempBuffer[200];
//		sprintf_s(tempBuffer, "X:%f, Y:%f, Z:%f, W:%f", x, y, z, w);
//		return string(tempBuffer);
//	}
//}
