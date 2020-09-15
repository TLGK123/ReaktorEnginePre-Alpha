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

#ifndef TmingEngine_Engine_Math_Determinant_h_
#define TmingEngine_Engine_Math_Determinant_h_

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

namespace TmingEngine
{
	ENGINE_CLASS class Determinant
	{
	public:
		std::vector<std::vector<float>> determinant;
		int row = 0;
		int cloumn = 0;

		//行列式一定是方阵
		Determinant(int n, std::initializer_list<float> il)
		{
			row = n;
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
			determinant = vec;
		}

		//行列式一定是方阵
		Determinant(int n, std::vector<float> il)
		{
			row = n;
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
			determinant = vec;
		}

		Determinant(int n)
		{
			row = n;
			cloumn = n;
			std::vector<std::vector<float>> vec(row, std::vector<float>(cloumn));//初始层数，赋值
			determinant = vec;
		}

		Determinant()
		{
			row = 4;
			cloumn = 4;
			std::vector<std::vector<float>> vec(row, std::vector<float>(cloumn));//初始层数，赋值
			determinant = vec;

			for (int i = 0; i < row; i++)
			{
				for (int j = 0; j < cloumn; j++)
				{
					for (int k = 0; k < cloumn; k++)
					{
						if (i == j)
						{
							determinant[i][j] = 1;
						}
					}
				}
			}
		}

		std::vector<float>& operator[](int i)
		{
			return determinant[i];
		}

		//行列式的值
		float Det()
		{
			if (row == 1 && cloumn == 1)
			{
				return determinant[0][0];
			}
			else
			{
				float detValue = 0;
				int i = 0;
				{
					for (int j = 0; j < cloumn; j++)
					{
						float f1 = determinant[i][j];
						float f2 = AlgebraicCofactor(i, j);

						detValue = detValue + f1 * f2;
					}
				}
				return detValue;
			}
		}

		//Aij 的余子式
		Determinant Cofactor(int m, int n)
		{
			std::vector<float> data;
			for (int i = 0; i < row; i++)
			{
				for (int j = 0; j < cloumn; j++)
				{
					if (i == m || n == j)
					{
						continue;
					}
					else
					{
						float c = determinant[i][j];
						data.push_back(c);
					}
				}
			}

			//row == cloumn
			Determinant lessDet(row - 1, data);
			return lessDet;
		}

		//Aij 代数余子式的值
		float AlgebraicCofactor(int m, int n)
		{
			float sign = (m + n) % 2 == 0 ? 1 : -1;
			return sign * Cofactor(m, n).Det();
		}

		friend std::ostream& operator<<(std::ostream& stream, Determinant c)
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
	};
}

#endif // TmingEngine_Engine_Math_Determinant_h_