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
#include <math.h>
#include "Radian.h"
#include <string>
#include <stdio.h>
#include <initializer_list>
#include <vector>
#include <sstream>
#include <iostream>
#include <iomanip>

using namespace std;
namespace TmingEngine
{
	ENGINE_CLASS class Matrix
	{
	public:
		vector<vector<float>> matrix;
		int row = 0;
		int cloumn = 0;

		Matrix(int m, int n, initializer_list<float> il)
		{
			row = m;
			cloumn = n;
			vector<vector<float>> vec(row, vector<float>(cloumn));//初始层数，赋值
			int index = 0;

			for (auto beg = il.begin(); beg != il.end(); ++beg)
			{
				int	i = index / cloumn;
				int	j = index % cloumn;
				index++;
				vec[i][j] = *beg;
			}
			matrix = vec;
		}

		Matrix(int m, int n)
		{
			row = m;
			cloumn = n;
			vector<vector<float>> vec(row, vector<float>(cloumn));//初始层数，赋值
			matrix = vec;
		}

		vector<float>& operator[](int i)
		{
			return matrix[i];
		}

		Matrix operator * (Matrix mat)const
		{
			Matrix reslut(row, mat.cloumn);
			if (cloumn != mat.row)
			{
				std::cout << "不满足矩阵【乘法】计算格式 " << std::endl;
				return reslut;
			}

			for (int i = 0; i < row; i++)
			{
				for (int j = 0; j < mat.cloumn; j++)
				{
					for (int k = 0; k < cloumn; k++)
					{
						auto a = matrix[i][k];
						auto b = mat[k][j];
						reslut[i][j] += a * b;
					}
				}
			}
			return reslut;
		}

		Matrix operator * (float num)const
		{
			Matrix reslut(row, cloumn);

			for (int i = 0; i < row; i++)
			{
				for (int j = 0; j < cloumn; j++)
				{
					reslut[i][j] = reslut[i][j] * num;
				}
			}
			return reslut;
		}

		Matrix operator + (float num)const
		{
			Matrix result(row, cloumn);
			for (int x = 0; x < row; x++)
			{
				for (int y = 0; y < cloumn; y++)
				{
					result[x][y] = matrix[x][y] + num;
				}
			}
			return result;
		}

		Matrix operator - (float num)const
		{
			Matrix result(row, cloumn);
			for (int x = 0; x < row; x++)
			{
				for (int y = 0; y < cloumn; y++)
				{
					result[x][y] = matrix[x][y] - num;
				}
			}
			return result;
		}

		Matrix operator + (Matrix mat)const
		{
			Matrix result(row, cloumn);

			if (row != mat.row || cloumn != mat.cloumn)
			{
				std::cout << "不满足矩阵【加法】计算格式 " << std::endl;
				return result;
			}

			for (int x = 0; x < row; x++)
			{
				for (int y = 0; y < cloumn; y++)
				{
					result[x][y] = matrix[x][y] + mat[x][y];
				}
			}
			return result;
		}

		Matrix operator - (Matrix mat)const
		{
			Matrix result(row, cloumn);

			if (row != mat.row || cloumn != mat.cloumn)
			{
				std::cout << "不满足矩阵【减法】计算格式 " << std::endl;
				return result;
			}

			for (int x = 0; x < row; x++)
			{
				for (int y = 0; y < cloumn; y++)
				{
					result[x][y] = matrix[x][y] - mat[x][y];
				}
			}
			return result;
		}

		friend ostream& operator<<(ostream& stream, Matrix c)
		{
			std::string s = "";
			for (int x = 0; x < c.row; x++)
			{
				s += "|";
				for (int y = 0; y < c.cloumn; y++)
				{
					ostringstream oss;
					oss << setiosflags(ios::fixed | ios::right) << setw(8) << setprecision(2) << c[x][y];
					s += string(oss.str()) + string(" ");
				}
				s += "|";
				s += string("\n");
			}
			stream << s;
			return stream;
		}
	};
}