/*
			This file is part of:
				TmingEngine
			https://github.com/xiaomingfun/TmingEngine

   Copyright 2018 - 2020 TmingEngine

   File creator: littleblue

   TmingEngine is open-source software and you can redistribute it and/or modify
   it under the terms of the License; besides, anyone who use this file/software must include this copyright announcement.

   Licensed under the Apache License, Version 2.0 (the "License");
   you may not use this file except in compliance with the License.
   You may obtain a copy of the License at

	   http://www.apache.org/licenses/LICENSE-2.0

   Unless required by applicable law or agreed to in writing, software
   distributed under the License is distributed on an "AS IS" BASIS,
   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
   See the License for the specific language governing permissions and
   limitations under the License.
*/

#ifndef TmingEngine_Engine_Math_Matrix_h_
#define TmingEngine_Engine_Math_Matrix_h_

#include <math.h>
#include <stdio.h>

#include <string>
#include <initializer_list>
#include <vector>
#include <sstream>
#include <iostream>
#include <iomanip>

#include "Core/Math/Radian.h"
#include "Core/Math/Vector3.h"
#include "Core/EngineDefs.h"

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

		Matrix()
		{
			row = 4;
			cloumn = 4;
			vector<vector<float>> vec(row, vector<float>(cloumn));//初始层数，赋值
			matrix = vec;

			for (int i = 0; i < row; i++)
			{
				for (int j = 0; j < cloumn; j++)
				{
					for (int k = 0; k < cloumn; k++)
					{
						if (i == j)
						{
							matrix[i][j] = 1;
						}
					}
				}
			}
		}

		vector<float>& operator[](int i)
		{
			return matrix[i];
		}

		Matrix Transpose()
		{
			Matrix reslut(cloumn , row);
			for (int i = 0; i < row; i++)
			{
				for (int j = 0; j < cloumn; j++)
				{
					reslut[j][i] = matrix[i][j];
				}
			}
			return reslut;
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

		Matrix operator * (Vector3 point)const
		{
			Matrix reslut(4, 1);

			if (cloumn != 4)
			{
				std::cout << "不满足矩阵【乘法】计算格式 " << std::endl;
				return reslut;
			}

			Matrix p1(4, 1,
				{
				  point.x,
				  point.y,
				  point.z,
				  1,
				});

			for (int i = 0; i < row; i++)
			{
				for (int j = 0; j < p1.cloumn; j++)
				{
					for (int k = 0; k < cloumn; k++)
					{
						auto a = matrix[i][k];
						auto b = p1[k][j];
						reslut[i][j] += a * b;
					}
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

		operator Vector3()
		{
			if (row < 3)
			{
				std::cout << "不满足自动矩阵 转 Vector3 格式 " << std::endl;
				return Vector3();
			}

			return Vector3(matrix[0][cloumn - 1], matrix[1][cloumn - 1], matrix[2][cloumn - 1]);
		}


	};
}

#endif //TmingEngine_Engine_Math_Matrix_h_