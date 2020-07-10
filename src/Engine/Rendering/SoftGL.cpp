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

#include "Rendering/SoftGL.hpp"

#include "Core/Math/Vector3.h"
#include "Core/Math/Matrix.h"
#include "Rendering/Vertex.hpp"
#include "Rendering/Light.hpp"
#include "Rendering/IShader.hpp"
#include "tgaimage/tgaimage.h"

namespace TmingEngine
{
	Matrix LookAt(Vector3 eye, Vector3 center, Vector3 up)
	{
		Vector3 R, U, D;  // x y z
		D = (eye - center).Normalize();    //从观察的物体到相机的一个方向向量
		R = (up.Cross(D)).Normalize();
		U = (D.Cross(R)).Normalize();

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

	//// left == right, bottom == top ,near ,far  simplified  Matrix
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
				1 / r , 0, 0, 0,
				0, 1 / t , 0,0,
				0, 0, -2 / (f - n), -(f + n) / (f - n),
				0,0,0,1,
			});
		return orthographic;
	}

	Matrix Viewport(int x, int y, int width, int heigh)
	{
		int d = 255;
		Matrix mat(4, 4,
			{
				width / 2.0f ,0,0, x + width / 2.0f ,
				0 ,heigh / 2.0f ,0, y + heigh / 2.0f ,
				0 ,0 ,d / 2.0f, d / 2.0f ,
				0 ,0 ,d / 2.0f, 1 ,
			});
		return mat;
	}

	void line(int x0, int y0, int x1, int y1, TGAImage& image, TGAColor color) {
		bool steep = false;
		if (std::abs(x0 - x1) < std::abs(y0 - y1)) {
			std::swap(x0, y0);
			std::swap(x1, y1);
			steep = true;
		}
		if (x0 > x1) {
			std::swap(x0, x1);
			std::swap(y0, y1);
		}
		int dx = x1 - x0;
		int dy = y1 - y0;
		int derror2 = std::abs(dy) * 2;
		int error2 = 0;
		int y = y0;
		for (int x = x0; x <= x1; x++) {
			if (steep) {
				image.set(y, x, color);
			}
			else {
				image.set(x, y, color);
			}
			error2 += derror2;
			if (error2 > dx) {
				y += (y1 > y0 ? 1 : -1);
				error2 -= dx * 2;
			}
		}
	}

	void line(Vector2 x, Vector2 y, TGAImage& image, TGAColor color)
	{
		line(x.x, x.y, y.x, y.y, image, color);
	}

	void triangle(Vector2 t0, Vector2 t1, Vector2 t2, TGAImage& image, TGAColor color) {
		line(t0, t1, image, color);
		line(t1, t2, image, color);
		line(t2, t0, image, color);
	}

	void drawBox(Vector2 miniP, Vector2 maxP, TGAImage& image, TGAColor color)
	{
		line(miniP.x, miniP.y, maxP.x, miniP.y, image, color);
		line(miniP.x, miniP.y, miniP.x, maxP.y, image, color);
		line(miniP.x, maxP.y, maxP.x, maxP.y, image, color);
		line(maxP.x, miniP.y, maxP.x, maxP.y, image, color);
	}

	void fillTriangleFromEdge(Vector2 A, Vector2 B, Vector2 C, TGAImage& image, TGAColor color)
	{
		Vector2* boxs = findTriangleBox(A, B, C);
		Vector2 minPoint = boxs[0];
		Vector2 maxPoint = boxs[1];
		//drawBox(minPoint, maxPoint,image,color);

		TGAColor col = TGAColor(rand() % 255, rand() % 255, rand() % 255, 255);

		for (int y = minPoint.y; y <= maxPoint.y; y += 1)
		{
			for (int x = minPoint.x; x <= maxPoint.x; x += 1)
			{
				Vector2 P = Vector2(x, y);

				Vector2 AB = B - A; //Vector AB
				Vector2 AP = P - A; //Vector AP

				Vector2 BC = C - B; //Vector BC
				Vector2 BP = P - B; //Vector BP

				Vector2 CA = A - C; //Vector CA
				Vector2 CP = P - C; //Vector CP

				float fabp = AB.Cross(AP);
				float fbcp = BC.Cross(BP);
				float fcap = CA.Cross(CP);

				if (fabp <= 0 && fbcp <= 0 && fcap <= 0)   //一般使用顺时针 点 顺序表示正面
				{
					image.set(x, y, col);
				}
			}
		}
	}

	void fillTriangleFromEdge(Vector3 t0, Vector3 t1, Vector3 t2, TGAImage& image, TGAColor color)
	{
		Vector2 A, B, C;
		A = Vector2(t0.x, t0.y);
		B = Vector2(t1.x, t1.y);
		C = Vector2(t2.x, t2.y);
		Vector2* boxs = findTriangleBox(A, B, C);
		Vector2 minPoint = boxs[0];
		Vector2 maxPoint = boxs[1];
		//drawBox(minPoint, maxPoint,image,color);

		Vector3 N = ((t1 - t0).Cross(t2 - t0)).Normalize();
		float intensity = N.Dot(sunlitght.Direction);

		if (intensity < 0)
		{
			//It means that the light comes from behind the polygon.
			// Back-face culling
			return;
		}

		TGAColor col = TGAColor(intensity * 255, intensity * 255, intensity * 255, 255);

		for (int y = minPoint.y; y <= maxPoint.y; y += 1)
		{
			for (int x = minPoint.x; x <= maxPoint.x; x += 1)
			{
				Vector2 P = Vector2(x, y);

				Vector2 AB = B - A; //Vector AB
				Vector2 AP = P - A; //Vector AP

				Vector2 BC = C - B; //Vector BC
				Vector2 BP = P - B; //Vector BP

				Vector2 CA = A - C; //Vector CA
				Vector2 CP = P - C; //Vector CP

				float fabp = AB.Cross(AP);
				float fbcp = BC.Cross(BP);
				float fcap = CA.Cross(CP);

				if (fabp <= 0 && fbcp <= 0 && fcap <= 0)   //一般使用顺时针 点 顺序表示正面
				{
					image.set(x, y, col);
				}
			}
		}
	}

	void fillTriangleFromEdgeWitchZbuffer(Vector3 t0, Vector3 t1, Vector3 t2, int frameWidth, int frameHeight, TGAImage& image, TGAColor color, int* zbuffer)
	{
		Vector2* boxs = findTriangleBox(t0, t1, t2);

		Vector2 minPoint = boxs[0];
		Vector2 maxPoint = boxs[1];
		//drawBox(minPoint, maxPoint,image,color);

		Vector3 N = ((t1 - t0).Cross(t2 - t0)).Normalize();
		float intensity = N.Dot(sunlitght.Direction.Normalize());

		if (intensity < 0)
		{
			//It means that the light comes from behind the polygon.
			// Back-face culling
			return;
		}

		TGAColor col = TGAColor(intensity * 255, intensity * 255, intensity * 255, 255);

		for (int y = minPoint.y; y <= maxPoint.y; y += 1)
		{
			for (int x = minPoint.x; x <= maxPoint.x; x += 1)
			{
				Vector3 P = Vector3(x, y, 0);
				Vector3 barycent = barycentricCoordinateCrossProduct(t0, t1, t2, P);
				P.z = t0.z * barycent.x + t1.z * barycent.y + t2.z * barycent.z;

				if (barycent.x >= 0 && barycent.y >= 0 && barycent.z >= 0)
				{
					if (P.x >= 0 && P.y >= 0 && P.x <= frameWidth && P.y <= frameHeight)
					{
						int cacheDeep = zbuffer[int(x + y * frameWidth)];
						if (P.z < cacheDeep)
						{
							bool discard = shader->Fragment(col);
							if (!discard)
							{
								image.set(P.x, P.y, col);
								zbuffer[int(x + y * frameWidth)] = P.z;
							}
						}
						else
						{
							int a = 0;
							;
						}
					}
					else
					{
						;
					}
				}
			}
		}
	}

	void fillTriangleFromEdgeWitchZbuffer(Vertex v1, Vertex v2, Vertex v3, int frameWidth, int frameHeight, TGAImage& image, TGAColor color, int* zbuffer)
	{
		Vector2* boxs = findTriangleBox(v1.Position, v2.Position, v3.Position);

		Vector2 minPoint = boxs[0];
		Vector2 maxPoint = boxs[1];

		Matrix normals(3, 3, {
		v1.Normal.x,v2.Normal.x,v3.Normal.x,
		v1.Normal.y,v2.Normal.y,v3.Normal.y,
		v1.Normal.z,v2.Normal.z,v3.Normal.z,
			});

		for (int y = minPoint.y; y <= maxPoint.y; y += 1)
		{
			for (int x = minPoint.x; x <= maxPoint.x; x += 1)
			{
				Vector3 P = Vector3(x, y, 0);
				Vector3 barycent = barycentricCoordinateCrossProduct(v1.Position, v2.Position, v3.Position, P);
				P.z = v1.Position.z * barycent.x + v2.Position.z * barycent.y + v3.Position.z * barycent.z;

				Matrix barycents(3, 1, {
					   barycent.x,
					   barycent.y,
					   barycent.z,
					});

				auto interpolatedNormal = normals * barycents;
				Vector3 pixelNormal = Vector3(interpolatedNormal[0][0], interpolatedNormal[1][0], interpolatedNormal[2][0]).Normalize();

				float intensity = pixelNormal.Dot(sunlitght.Direction.Normalize());

				if (intensity < 0)
				{
					//It means that the light comes from behind the polygon.
					// Back-face culling
					return;
				}

				TGAColor col = TGAColor(intensity * 255, intensity * 255, intensity * 255, 255);

				if (barycent.x >= 0 && barycent.y >= 0 && barycent.z >= 0)
				{
					if (P.x >= 0 && P.y >= 0 && P.x <= frameWidth && P.y <= frameHeight)
					{
						int cacheDeep = zbuffer[int(x + y * frameWidth)];
						if (P.z < cacheDeep)
						{
							bool discard = shader->Fragment(col, barycent);
							if (!discard)
							{
								image.set(P.x, P.y, col);
								zbuffer[int(x + y * frameWidth)] = P.z;
							}
						}
						else
						{
							int a = 0;
							;
						}
					}
					else
					{
						;
					}
				}
			}
		}
	}

	void fillTriangleLinerScan(Vector2 t0, Vector2 t1, Vector2 t2, TGAImage& image, TGAColor color)
	{
		//根据 点的y坐标 从上到下排序
		if (t0.y < t1.y)
		{
			std::swap(t0, t1);
		}

		if (t0.y < t2.y)
		{
			std::swap(t0, t2);
		}

		if (t1.y < t2.y)
		{
			std::swap(t1, t2);
		}

		if (t1.y == t2.y)
		{
			fillUpTriangle(t0, t1, t2, image, color);
		}
		else if (t1.y == t0.y)
		{
			fillDownTriangle(t2, t1, t0, image, color);
		}
		else
		{
			//直线表达 两点式
			Vector2 t4;
			t4.y = t1.y;
			t4.x = (t0.x - t2.x) / (t0.y - t2.y) * (t4.y - t2.y) + t2.x;

			fillUpTriangle(t0, t1, t4, image, color);

			fillDownTriangle(t2, t1, t4, image, color);
			line(t1, t4, image, white);
		}

		Vector2* box = findTriangleBox(t0, t1, t2);
		auto b1 = box[0];
		auto b2 = box[1];

		drawBox(b1, b2, image, color);
		;
	}

	void fillUpTriangle(Vector2 t0, Vector2 t1, Vector2 t2, TGAImage& image, TGAColor color)
	{
		for (int i = 0; i < (t0.y - t1.y); i += 3)
		{
			Vector2 p1, p2;
			p1.y = p2.y = t1.y + i;
			p1.x = (t0.x - t1.x) / (t0.y - t1.y) * (p1.y - t1.y) + t1.x;
			p2.x = (t0.x - t2.x) / (t0.y - t2.y) * (p2.y - t2.y) + t2.x;
			line(p1, p2, image, color);
		}
	}

	void fillDownTriangle(Vector2 t0, Vector2 t1, Vector2 t2, TGAImage& image, TGAColor color)
	{
		for (int i = 0; i < (t1.y - t0.y); i++)
		{
			Vector2 p1, p2;
			p1.y = p2.y = t1.y - i;
			p1.x = (t0.x - t1.x) / (t0.y - t1.y) * (p1.y - t1.y) + t1.x;
			p2.x = (t0.x - t2.x) / (t0.y - t2.y) * (p2.y - t2.y) + t2.x;
			line(p1, p2, image, color);
		}
	}

	Vector2* findTriangleBox(Vector2 t0, Vector2 t1, Vector2 t2)
	{
		Vector2 minPoint, maxPoint;
		Vector2 points[3], box[2];
		points[0] = t0;
		points[1] = t1;
		points[2] = t2;

		minPoint.x = points[0].x;
		minPoint.y = points[0].y;

		maxPoint.x = points[0].x;
		maxPoint.y = points[0].y;
		for (int i = 0; i < 3; i++)
		{
			if (minPoint.x > points[i].x)
			{
				minPoint.x = points[i].x;
			}
			if (minPoint.y > points[i].y)
			{
				minPoint.y = points[i].y;
			}

			if (maxPoint.x < points[i].x)
			{
				maxPoint.x = points[i].x;
			}
			if (maxPoint.y < points[i].y)
			{
				maxPoint.y = points[i].y;
			}
		}

		box[0] = minPoint;
		box[1] = maxPoint;

		return box;
	}

	Vector2* findTriangleBox(Vector3 t0, Vector3 t1, Vector3 t2)
	{
		Vector3 minPoint, maxPoint;
		Vector3 points[3];
		Vector2  box[2];
		points[0] = t0;
		points[1] = t1;
		points[2] = t2;

		minPoint.x = points[0].x;
		minPoint.y = points[0].y;
		minPoint.z = points[0].z;

		maxPoint.x = points[0].x;
		maxPoint.y = points[0].y;
		maxPoint.z = points[0].z;
		for (int i = 0; i < 3; i++)
		{
			if (minPoint.x > points[i].x)
			{
				minPoint.x = points[i].x;
			}
			if (minPoint.y > points[i].y)
			{
				minPoint.y = points[i].y;
			}
			if (minPoint.z > points[i].z)
			{
				minPoint.z = points[i].z;
			}

			if (maxPoint.x < points[i].x)
			{
				maxPoint.x = points[i].x;
			}
			if (maxPoint.y < points[i].y)
			{
				maxPoint.y = points[i].y;
			}
			if (maxPoint.z < points[i].z)
			{
				maxPoint.z = points[i].z;
			}
		}

		box[0] = Vector2(minPoint.x, minPoint.y);
		box[1] = Vector2(maxPoint.x, maxPoint.y);

		return box;
	}

	Vector3 barycentricCoordinate(Vector3 a, Vector3 b, Vector3 c, Vector3 p)
	{
		auto v0 = b - a;
		auto v1 = c - a;
		auto v2 = p - a;

		float d00 = v0.Dot(v0);
		float d01 = v0.Dot(v1);
		float d11 = v1.Dot(v1);
		float d20 = v2.Dot(v0);
		float d21 = v2.Dot(v1);
		float denom = d00 * d11 - d01 * d01;

		float v = (d11 * d20 - d01 * d21) / denom;
		float w = (d00 * d21 - d01 * d20) / denom;
		float u = 1.0f - v - w;

		return Vector3(u, v, w);
	}

	Vector3 barycentricCoordinateCrossProduct(Vector3 a, Vector3 b, Vector3 c, Vector3 p)
	{
		// p = u * a + v * b + w * c;
		// p = u * a + v * b + (1 - u - v) * c;
		// p = u * (a - c)+ v * (b - c ) + c;
		// p - c = u * (a - c)+ v * (b - c );
		//  u * (a - c)+ v * (b - c ) + (c - p ) = 0
		//				  |(a - c)  |
		//  (u , v , 1) * |(b - c)  |  = 0
		//                |(c - p)  |
		//======>
		//				  |(a - c)x  |
		//  (u , v , 1) * |(b - c)x  |  = 0
		//                |(c - p)x  |

		//				  |(a - c)y  |
		//  (u , v , 1) * |(b - c)y  |  = 0
		//                |(c - p)y  |

		auto v1 = a - c;
		auto v2 = b - c;
		auto v3 = c - p;
		auto u = Vector3(v1.x, v2.x, v3.x).Cross(Vector3(v1.y, v2.y, v3.y));
		if (std::abs(u.z) > 1e-2)
		{
			return Vector3(1.0f - (u.x + u.y) / u.z, u.x / u.z, u.y / u.z);
		}
		else
		{
			return Vector3(-1, 1, 1);
		}
	}

	Vector3 barycentricCoordinateCrossProduct(Vertex a, Vertex b, Vertex c, Vertex p)
	{
		auto v1 = a.Position - c.Position;
		auto v2 = b.Position - c.Position;
		auto v3 = c.Position - p.Position;

		auto u = Vector3(v1.x, v2.x, v3.x).Cross(Vector3(v1.y, v2.y, v3.y));
		if (std::abs(u.z) > 1e-2)
		{
			return Vector3(1.0f - (u.x + u.y) / u.z, u.x / u.z, u.y / u.z);
		}
		else
		{
			return Vector3(-1, 1, 1);
		}

		return Vector3();
	}
} // namespace TmingEngine