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

#pragma once

#ifndef Game_hpp
#define Game_hpp

#include <stdio.h>
#include "Core/SubSystem.h"
#include "Core/Context.h"
#include "Plantform/Windows/Widget.h"
#include "im.h"
#include "tgaimage/tgaimage.h"
#include "angelscript.h"
#include <scriptstdstring/scriptstdstring.h>
#include <scriptbuilder/scriptbuilder.h>
#include "Plantform/FileSystem/FileSystem.h"
#include "Core/Math/Vector2.h"
#include "Core/Math/Vector3.h"
#include "Core/Math/Matrix.h"
#include "Rendering/Model.hpp"
#include "Rendering/Light.hpp"
#include "Rendering/GouraudShader.hpp"
#include "Rendering/Vertex.hpp"
																																																							
namespace TmingEngine
{
	class Game :public Widget
	{
	public:

		Game(Context* context)
		{
			m_title = "Game";
		}
		~Game();

		void Begin();
		void Update();
		void End();

		unsigned int imageId;
		void SoftRender();

		Model testCharacter;
	};

	const TGAColor white = TGAColor(255, 255, 255, 255);
	const TGAColor red = TGAColor(255, 0, 0, 255);
	const TGAColor green = TGAColor(0, 255, 0, 255);
	const TGAColor blue = TGAColor(0, 0, 255, 255);

	void line(int x0, int y0, int x1, int y1, TGAImage& image, TGAColor color);
	void line(Vector2 x, Vector2 y, TGAImage& image, TGAColor color);
	void fillTriangleLinerScan(Vector2 t0, Vector2 t1, Vector2 t2, TGAImage& image, TGAColor color); //填充一个普通三角形
	void fillUpTriangle(Vector2 t0, Vector2 t1, Vector2 t2, TGAImage& image, TGAColor color); //填充一个底边平行 X 轴 ，顶点在上的三角形
	void fillDownTriangle(Vector2 t0, Vector2 t1, Vector2 t2, TGAImage& image, TGAColor color);//填充一个底边平行 X 轴 ，顶点在下的三角形
	Vector2* findTriangleBox(Vector2 t0, Vector2 t1, Vector2 t2);								//找到一个三角形最小包裹框

	void triangle(Vector2 t0, Vector2 t1, Vector2 t2, TGAImage& image, TGAColor color);
	void drawBox(Vector2 t0, Vector2 t1, TGAImage& image, TGAColor color);

	void fillTriangleFromEdge(Vector2 t0, Vector2 t1, Vector2 t2, TGAImage& image, TGAColor color);

	void fillTriangleFromEdge(Vector3 t0, Vector3 t1, Vector3 t2, TGAImage& image, TGAColor color);

	Vector2* findTriangleBox(Vector3 t0, Vector3 t1, Vector3 t2);

	Vector3 barycentricCoordinate(Vector3 a, Vector3 b, Vector3 c, Vector3 p);

	Vector3 barycentricCoordinateCrossProduct(Vector3 a, Vector3 b, Vector3 c, Vector3 p);

	Vector3 barycentricCoordinateCrossProduct(Vertex a, Vertex b, Vertex c, Vertex p);

	void fillTriangleFromEdgeWitchZbuffer(Vector3 t0, Vector3 t1, Vector3 t2, TGAImage& image, TGAColor color, int* zbuffer);

	void fillTriangleFromEdgeWitchZbuffer(Vertex v1, Vertex v2, Vertex v3, TGAImage& image, TGAColor color, int* zbuffer);

	Vector2 Matirx2x2(Vector2 p, float a, float b, float c, float d);

	Matrix LookAt(Vector3 eye, Vector3 center, Vector3 up);

	Matrix Viewport(int x, int y, int width, int heigh);

	Matrix Perspective(float l, float r, float b, float t, float n, float f);

	Matrix Perspective(float r, float t, float n, float f);

	Matrix Orthographic(float l, float r, float b, float t, float n, float f);

	Matrix Orthographic(float r, float t, float n, float f);
}

#endif