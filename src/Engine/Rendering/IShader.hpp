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
#include "tgaimage/tgaimage.h"

namespace TmingEngine
{
	class IShader
	{
	public:
		IShader() {};
		~IShader() {};

		Matrix porjection;
		Matrix view;
		Matrix model;
		Matrix viewPoint;

		void SetProjection(Matrix p)
		{
			porjection = p;
		}

		void SetView(Matrix v)
		{
			view = v;
		}

		void SetModel(Matrix m)
		{
			model = m;
		}

		void SetViewPoint(Matrix vp)
		{
			viewPoint = vp;
		}

		virtual Vector3 Vertex(Vector3 pos) = 0;
		virtual bool Fragment( TGAColor& color) = 0;
	};
}