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