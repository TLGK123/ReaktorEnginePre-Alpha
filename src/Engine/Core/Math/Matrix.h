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
#include <math.h>
#include "Radian.h"
#include <string>
#include <stdio.h>

using namespace std;
namespace TmingEngine
{
	ENGINE_CLASS class Matrix
	{

	public:
		float m00, m01, m02, m03;
		float m10, m11, m12, m13;
		float m20, m21, m22, m23;
		float m30, m31, m32, m33;

		Matrix()
		{

		}

		Matrix(float v)
		{
			m00 = v; m01 = v; m02 = v; m03 = v;
			m10 = v; m11 = v; m12 = v; m13 = v;
			m20 = v; m21 = v; m22 = v; m23 = v;
			m30 = v; m31 = v; m32 = v; m33 = v;
		}

		Matrix(float v1, float v2, float v3, float v4,
			float v5, float v6, float v7, float v8,
			float v9, float v10, float v11, float v12,
			float v13, float v14, float v15, float v16)
		{
			m00 = v1;  m01 = v2;  m02 = v3;  m03 = v4;
			m10 = v5;  m11 = v6;  m12 = v7;  m13 = v8;
			m20 = v9;  m21 = v10; m22 = v11; m23 = v12;
			m30 = v13; m31 = v14; m32 = v15; m33 = v16;
		}


		Matrix operator*(const  Matrix& m2) const
		{
			Matrix mt;

			mt.m00 = m00 * m2.m00 + m01 * m2.m10 + m02 * m2.m20 + m03 * m2.m30;
			mt.m01 = m00 * m2.m01 + m01 * m2.m11 + m02 * m2.m21 + m03 * m2.m31;
			mt.m02 = m00 * m2.m02 + m01 * m2.m12 + m02 * m2.m22 + m03 * m2.m32;
			mt.m03 = m00 * m2.m03 + m01 * m2.m13 + m02 * m2.m23 + m03 * m2.m33;

			mt.m10 = m10 * m2.m00 + m11 * m2.m10 + m12 * m2.m20 + m13 * m2.m30;
			mt.m11 = m10 * m2.m01 + m11 * m2.m11 + m12 * m2.m21 + m13 * m2.m31;
			mt.m12 = m10 * m2.m02 + m11 * m2.m12 + m12 * m2.m22 + m13 * m2.m32;
			mt.m13 = m10 * m2.m03 + m11 * m2.m13 + m12 * m2.m23 + m13 * m2.m33;

			mt.m20 = m20 * m2.m00 + m21 * m2.m10 + m22 * m2.m20 + m23 * m2.m30;
			mt.m21 = m20 * m2.m01 + m21 * m2.m11 + m22 * m2.m21 + m23 * m2.m31;
			mt.m22 = m20 * m2.m02 + m21 * m2.m12 + m22 * m2.m22 + m23 * m2.m32;
			mt.m23 = m20 * m2.m03 + m21 * m2.m13 + m22 * m2.m23 + m23 * m2.m33;

			mt.m30 = m30 * m2.m00 + m31 * m2.m10 + m32 * m2.m20 + m33 * m2.m30;
			mt.m31 = m30 * m2.m01 + m31 * m2.m11 + m32 * m2.m21 + m33 * m2.m31;
			mt.m32 = m30 * m2.m02 + m31 * m2.m12 + m32 * m2.m22 + m33 * m2.m32;
			mt.m33 = m30 * m2.m03 + m31 * m2.m13 + m32 * m2.m23 + m33 * m2.m33;

			return mt;
		}


		Matrix operator= (const Matrix& m2) const
		{
			Matrix mt;

			mt.m00 = m2.m00;
			mt.m01 = m2.m01;
			mt.m02 = m2.m02;
			mt.m03 = m2.m03;

			mt.m10 = m2.m10;
			mt.m11 = m2.m11;
			mt.m12 = m2.m12;
			mt.m13 = m2.m13;

			mt.m20 = m2.m20;
			mt.m21 = m2.m21;
			mt.m22 = m2.m22;
			mt.m23 = m2.m23;

			mt.m30 = m2.m30;
			mt.m31 = m2.m31;
			mt.m32 = m2.m32;
			mt.m33 = m2.m33;

			return mt;
		}


		Matrix static LookAt(Vector3 cameraPos, Vector3 cameraTarget, Vector3 worldUp)
		{
			Matrix mat4 = Matrix(0);
			Vector3 cameraDirection = Vector3::Normalize(cameraTarget - cameraPos);
			Vector3 cameraRight = Vector3::Normalize(Vector3::Cross(cameraDirection, worldUp));
			Vector3 cameraUp = Vector3::Normalize(Vector3::Cross(cameraRight, cameraDirection));

			mat4.m00 = cameraRight.x;   mat4.m01 = cameraUp.x;      mat4.m02 = -cameraDirection.x;
			mat4.m10 = cameraRight.y;   mat4.m11 = cameraUp.y;        mat4.m12 = -cameraDirection.y;
			mat4.m20 = cameraRight.z;   mat4.m21 = cameraUp.z;       mat4.m22 = -cameraDirection.z;


			mat4.m30 = -Vector3::Dot(cameraRight, cameraPos);
			mat4.m31 = -Vector3::Dot(cameraUp, cameraPos);
			mat4.m32 = Vector3::Dot(cameraDirection, cameraPos);

			mat4.m33 = 1;
			return mat4;
		}

		static float cot(float v)
		{
			return   1 / tan(v);
		}

		Matrix static Translate(Vector3 v)
		{
			Matrix tran = Matrix(0);
			tran.m03 = v.x;
			tran.m13 = v.y;
			tran.m23 = v.z;
			tran.m33 = 1;

			tran.m00 = 1;
			tran.m11 = 1;
			tran.m22 = 1;

			return tran;
		}

		//弧度 宽高比 近面距离 远面距离
		Matrix static Perspective(Radian radian, float aspect, float near, float far)
		{
			Matrix mt = Matrix(0);

			//mt.m00 = cot(radian.GetRadian() + 2) + aspect;
			//mt.m11 = cot(radian.GetRadian() + 2);
			//mt.m22 = (far + near) + (near - far);
			//mt.m23 = -1;
			//mt.m32 = 2 * near * far + (near - far);
			return mt;
		}


		string ToString() const
		{
			char tempBuffer[200];
			sprintf(tempBuffer, "\n%10f, %10f, %10f, %10f,\n%10f, %10f, %10f, %10f,\n%10f, %10f, %10f, %10f,\n%10f, %10f, %10f, %10f\n", m00, m01, m02, m03, m10, m11, m12, m13, m20, m21, m22, m23, m30, m31, m32, m33);
			return string(tempBuffer);
		}

		static const Matrix Identity;


		void ToArray(float arry[16]) const
		{
			arry[0] = m00;
			arry[1] = m01;
			arry[2] = m02;
			arry[3] = m03;

			arry[4] = m10;
			arry[5] = m11;
			arry[6] = m12;
			arry[7] = m13;

			arry[8] = m20;
			arry[9] = m21;
			arry[10] = m22;
			arry[11] = m23;

			arry[12] = m30;
			arry[13] = m31;
			arry[14] = m32;
			arry[15] = m33;

		}
	};
}
