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
#include "Core/Math/Vector4.h"
#include "Core/Math/Determinant.h"
#include "Core/EngineDefs.h"

namespace TmingEngine
{
	ENGINE_CLASS class Matrix
	{
	public:
		std::vector<std::vector<float>> matrix;
		int row = 0;
		int cloumn = 0;

		Matrix(int m, int n, std::initializer_list<float> il)
		{
			row = m;
			cloumn = n;
			std::vector<std::vector<float>> vec(row, std::vector<float>(cloumn));//初始层数，赋值
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
			std::vector<std::vector<float>> vec(row, std::vector<float>(cloumn));//初始层数，赋值
			matrix = vec;
		}

		Matrix()
		{
			row = 4;
			cloumn = 4;
			std::vector<std::vector<float>> vec(row, std::vector<float>(cloumn));//初始层数，赋值
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

		std::vector<float>& operator[](int i)
		{
			return matrix[i];
		}

		Matrix Transpose()
		{
			Matrix reslut(cloumn, row);
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
					reslut[i][j] = matrix[i][j] * num;
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

		friend std::ostream& operator<<(std::ostream& stream, Matrix c)
		{
			std::string s = "";
			for (int x = 0; x < c.row; x++)
			{
				s += "|";
				for (int y = 0; y < c.cloumn; y++)
				{
					std::ostringstream oss;
					oss << std::setiosflags(std::ios::fixed | std::ios::right) << std::setw(8) << std::setprecision(2) << c[x][y];
					s += std::string(oss.str()) + std::string(" ");
				}
				s += "|";
				s += std::string("\n");
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

		operator Vector4()
		{
			if (row < 4)
			{
				std::cout << "不满足自动矩阵 转 Vector3 格式 " << std::endl;
				return Vector4();
			}

			return Vector4(matrix[0][cloumn - 1], matrix[1][cloumn - 1], matrix[2][cloumn - 1],  matrix[3][cloumn - 1]);
		}

		operator Determinant()
		{
			return ToDeterminant();
		}

	private:
		//矩阵转换成对于行列式
		Determinant ToDeterminant()
		{
			Determinant result(row);
			if (row != cloumn)
			{
				std::cout << "不满足行列式必须是方阵 " << std::endl;
				return result;
			}

			for (int i = 0; i < row; i++)
			{
				for (int j = 0; j < cloumn; j++)
				{
					result[i][j] = matrix[i][j];
				}
			}
			return result;
		}
	public:
		//伴随矩阵
		Matrix Adjugate()
		{
			Matrix result(row, cloumn);
			Determinant sourceDet = ToDeterminant();
			for (int x = 0; x < row; x++)
			{
				for (int y = 0; y < cloumn; y++)
				{
					auto f2 = sourceDet.AlgebraicCofactor(x, y);	
					result[y][x] = f2;
				}
			}
			return result;
		}

		Matrix Inverse()
		{
			Matrix result(row, cloumn);
			Determinant sourceDet = ToDeterminant();
			float det = sourceDet.Det();
			if (det == 0)
			{
				std::cout << "矩阵对应行列式的值为0，矩阵不可逆" << std::endl;
				return result;
			}
			auto adj = Adjugate();
			//std::cout << "---adj---" << std::endl;
			//std::cout << adj << std::endl;
			result = adj * (1.0f / det);

			//std::cout << "---Inverse----" << std::endl;
			//std::cout << result << std::endl;

			return result;
		}
	};
}

#endif //TmingEngine_Engine_Math_Matrix_h_