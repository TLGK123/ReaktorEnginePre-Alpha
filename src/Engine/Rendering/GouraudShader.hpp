//The MIT License
//
//Copyright(c) 2016 - 2020 littleblue
//
//Permission is hereby granted, free of charge, to any person obtaining a copy
//of this softwareand associated documentation files(the "Software"), to deal
//in the Software without restriction, including without limitation the rights
//to use, copy, modify, merge, publish, distribute, sublicense, and / or sell
//copies of the Software, and to permit persons to whom the Software is furnished
//to do so, subject to the following conditions :
//
//The above copyright noticeand this permission notice shall be included in
//all copies or substantial portions of the Software.
//
//THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
//IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS
//FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.IN NO EVENT SHALL THE AUTHORS OR
//COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER
//IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
//CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

#include "Core/Math/Vector3.h"
#include "Core/Math/Matrix.h"
#include "IShader.hpp"

namespace TmingEngine
{
	class GouraudShader :public IShader
	{
	public:
		GouraudShader() {};
		~GouraudShader() {};

		Vector3 Vertex(Vector3 pos) override
		{
			Matrix p1(4, 1,
				{
				  pos.x,
				  pos.y,
				  pos.z,
				  1,
				});

			auto projectionPoint1 = porjection * view * model * p1;
			float w1 = projectionPoint1[3][0];
			Matrix t1(4, 4,
				{
				1 / w1 , 0 , 0 , 0 ,
				0 , 1 / w1 , 0 , 0 ,
				0 , 0 , 1 / w1 , 0 ,
				0 , 0 , 0 , 1 / w1 ,
				});

			//Í¸ÊÓ³ý·¨

			auto point1 = viewPoint * t1 * projectionPoint1;

			return Vector3(point1[0][0], point1[1][0], point1[2][0]);
		};

		bool Fragment(TGAColor& color , Vector3 barycent)override
		{
			//color = TGAColor(125,125,125,255);
			return false;
		}

		bool Fragment(TGAColor& color)override
		{
			//color = TGAColor(125,125,125,255);
			return false;
		}
	};
}