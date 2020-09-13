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

#ifndef TmingEngine_Engine_Rending_Camera_hpp_
#define TmingEngine_Engine_Rending_Camera_hpp_

#include <stdio.h>
#include <vector>

#include "Core/Context.h"
#include "Core/GameObject.hpp"
#include "Core/Math/Matrix.h"
#include "Core/Math/Vector3.h"
#include "Core/Math/Vector2.h"
#include "Rendering/SoftRending/SoftGL.hpp"

namespace TmingEngine
{
	ENGINE_CLASS class Camera
	{
	public:

		Camera()
		{
		}

		Vector3 position = Vector3(0, 2, 1);
		Vector3 center = Vector3(0, 0, 0);	//相机朝向原点
		Vector3 up = Vector3(0, 1, 0);		//相机向上（先假定的向上的一个方向）

		//http://www.songho.ca/opengl/gl_transform.html#modelview
		Matrix LookAt(Vector3 eye, Vector3 center, Vector3 up)
		{
			Vector3 R, U, D;  // x y z
			D = (eye - center).Normalize();		//从被观察的物体到相机的一个方向向量(相机面向的物体的相反方向) 相机的 Z轴正方向
			R = (up.Cross(D)).Normalize();		//假定的上 Cross 方向向量 ==相机X轴正方向
			U = (D.Cross(R)).Normalize();		//相机真正的向上的 Y轴 正方向

			// A * B = C
			// A-----a point dinfined in the new coordination space (camera space)
			// B-----a new base axis define in the A coordination
			// c-----the same point  aspect in the source coordination(world space)
			// now we know the A (world space point position) ,the
			// so B = A-1 * C   , A -1  = A transpose , a is a identity matrix
			// but we must let the origin ponit is the same

			Matrix Rotate(4, 4,
				{
				R.x , R.y , R.z , 0,
				U.x , U.y , U.z , 0,
				D.x , D.y , D.z , 0,
				0	, 0   , 0   , 1,
				});

			Matrix T(4, 4,
				{
				1, 0, 0, -eye.x,
				0, 1, 0, -eye.y,
				0, 0, 1, -eye.z,
				0, 0, 0,	1,
				});

			auto result = Rotate * T;
			return result;
		}

		Matrix LookAt()
		{
			return	LookAt(position, center, up);
		}

		// http://www.songho.ca/opengl/gl_projectionmatrix.html
		// left right bottom ,top ,near ,far
		Matrix Perspective(float l, float r, float b, float t, float n, float f)
		{
			Matrix prespective(4, 4,
				{
					2 * n / (r - l) , 0,(r + l) / (r - l),0,
					0, 2 * n / (t - b) ,(t + b) / (t - b),0,
					0,0, -(f + n) / (f - n),-2 * f * n / (f - n),
					0,0,-1,0,
				});
			return prespective;
		}

		// left == right, bottom == top ,near ,far  simplified  Matrix
		Matrix Perspective(float r, float t, float n, float f)
		{
			//r + l = 0;
			//r - l = 2r; width

			//t + b =0;
			//t - b =2t  height

			Matrix perspective(4, 4,
				{
					n / r ,0,0,0,
					0, n / t,0, 0,
					0,0, -(f + n) / (f - n),-2 * f * n / (f - n),
					0,0,-1,0,
				});
			return perspective;
		}

		Matrix Orthographic(float l, float r, float b, float t, float n, float f)
		{
			Matrix orthographic(4, 4,
				{
					2 / (r - l) , 0, 0, -(r + l) / (r - l),
					0, 2 / (t - b) , 0, -(t + b) / (t - b),
					0, 0, -2 / (f - n), -(f + n) / (f - n),
					0,0,0,1,
				});
			return orthographic;
		}

		Matrix Orthographic(float r, float t, float n, float f)
		{
			Matrix orthographic(4, 4,
				{
					1.0f / r , 0, 0, 0,
					0, 1.0f / t , 0,0,
					0, 0, -2.0f / (f - n), -(f + n) / (f - n),
					0,0,0,1,
				});
			return orthographic;
		}

		Matrix Viewport(int x, int y, int width, int heigh)
		{
			float d = 255;
			Matrix mat(4, 4,
				{
					width / 2.0f ,0,0, x + width / 2.0f ,
					0 ,heigh / 2.0f ,0, y + heigh / 2.0f ,
					0 ,0 ,d /2.0f, d/2.0f ,
					0 ,0 ,0, 1 ,
				});
			return mat;
		}
	};
}
#endif // TmingEngine_Engine_Rending_Camera_hpp_ 