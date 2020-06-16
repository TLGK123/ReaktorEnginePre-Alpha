//The MIT License
//
//Copyright(c) 2018 - 2019 littleblue
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
#pragma once

#include "../EngineDefs.h"
#include <string>
#include "Vector3.h"
#include "Vector2.h"
#include <math.h>
#include "Radian.h"
#include <string>
#include <stdio.h>
#include <initializer_list>

using namespace std;
namespace TmingEngine
{
	template <int m = 4, int n = 4 >
	ENGINE_CLASS class Matrix
	{
	public:
		float** matrix;
		int row = m;
		int cloumn = n;

		void GetSpace()
		{
			matrix = (float**)malloc(row * sizeof(float*));
			for (int i = 0; i < row; i++)
				matrix[i] = (float*)malloc(cloumn * sizeof(float));
			for (int i = 0; i < row; i++)
			{
				for (int j = 0; j < cloumn; j++)
				{
					matrix[i][j] = 0;
				}
			}
		}

		Matrix()
		{
			GetSpace();
		}

		Matrix(initializer_list<float> il)
		{
			GetSpace();
			int index = 0;
			for (auto beg = il.begin(); beg != il.end(); ++beg)
			{
				int	i = index / cloumn;
				int	j = index % cloumn;
				index++;
				matrix[i][j] = *beg;
			}
		}

		float*& operator[](int i)
		{
			return matrix[i];
		}

		//Matrix<2,1> operator * (const Vector2 p)const
		//{
		//	return Matrix<2, 1> aa ({ matrix[0][0] * p.x + matrix[0][1] * p.y, matrix[1][0] * p.x + matrix[1][1] * p.y });
		//}
	};
}
