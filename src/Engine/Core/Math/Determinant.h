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

		float Det()
		{
			if (row ==2 && cloumn==2)
			{

			}
		}
	};
}

#endif // TmingEngine_Engine_Math_Determinant_h_