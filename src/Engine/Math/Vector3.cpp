
//= INCLUDES =======
#include "Vector3.h"
//==================

//= NAMESPACES =====
using namespace std;
//==================

namespace TmingEngine::Math
{
	const Vector3 Vector3::Zero(0.0f, 0.0f, 0.0f);
	const Vector3 Vector3::One(1.0f, 1.0f, 1.0f);
	const Vector3 Vector3::Left(-1.0f, 0.0f, 0.0f);
	const Vector3 Vector3::Right(1.0f, 0.0f, 0.0f);
	const Vector3 Vector3::Up(0.0f, 1.0f, 0.0f);
	const Vector3 Vector3::Down(0.0f, -1.0f, 0.0f);
	const Vector3 Vector3::Forward(0.0f, 0.0f, 1.0f);
	const Vector3 Vector3::Back(0.0f, 0.0f, -1.0f);
	const Vector3 Vector3::Infinity(numeric_limits<float>::infinity(), numeric_limits<float>::infinity(), numeric_limits<float>::infinity());
	const Vector3 Vector3::InfinityNeg(-numeric_limits<float>::infinity(), -numeric_limits<float>::infinity(), -numeric_limits<float>::infinity());

	string Vector3::ToString() const
	{
		char tempBuffer[200];
		sprintf_s(tempBuffer, "X:%f, Y:%f, Z:%f", x, y, z);
		return string(tempBuffer);
	}
}
