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

#include "Game.hpp"

namespace TmingEngine
{
	TmingEngine::Game::~Game()
	{
	}

	void TmingEngine::Game::Begin()
	{
		testCharacter.Init(FileSystem::getPath("resources/objects/character/_2.obj"));

		SoftRender();
	}

	const int gameWidth = 500;
	const int gameHeight = 500;

	void TmingEngine::Game::Update()
	{
		bool p_open = true;
		ImGui::SetNextWindowSize(Vector2(640, 360), ImGuiCond_FirstUseEver);
		if (!ImGui::Begin("Game", &p_open))
		{
			ImGui::End();
			return;
		}
		ImTextureID my_tex_id = (void*)imageId;
		float my_tex_w = gameWidth;
		float my_tex_h = gameHeight;

		ImGui::Text("%.0fx%.0f", my_tex_w, my_tex_h);
		//----------------------------------------------------------------- -1 -1  Image reversal
		ImGui::Image(my_tex_id, Vector2(my_tex_w, my_tex_h), Vector2(0, 0), Vector2(-1, -1), ImColor(255, 255, 255, 255), ImColor(255, 255, 255, 128));
		ImGui::End();
	}

	void TmingEngine::Game::End()
	{
	}

	Light sunlitght;
	void TmingEngine::Game::SoftRender()
	{
		glGenTextures(1, &imageId);

		glBindTexture(GL_TEXTURE_2D, imageId);
		// set the texture wrapping parameters
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		// set texture wrapping to GL_REPEAT (default wrapping method)
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		// set texture filtering parameters
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		//// load image, create texture and generate mipmaps
		int width, height, nrChannels;

		TGAImage image(gameWidth, gameHeight, TGAImage::RGB);

		Vector2 t0[3] = { Vector2(40, 40),   Vector2(250, 300) , Vector2(350, 100) };
		Vector2 t1[3] = { Vector2(380, 50),  Vector2(450, 10),   Vector2(370, 180) };
		Vector2 t2[3] = { Vector2(180, 350), Vector2(120, 260), Vector2(130, 400) };
		///-----step 1
		/*
		triangle(t0[0], t0[1], t0[2], image, red);
		fillTriangleFromEdge(t0[0], t0[1], t0[2], image, red);

		triangle(t1[0], t1[1], t1[2], image, blue);
		fillTriangleLinerScan(t1[0], t1[1], t1[2], image, blue);

		triangle(t2[0], t2[1], t2[2], image, green);
		fillTriangleLinerScan(t2[0], t2[1], t2[2], image, green);
		*/

		//-----step 2

		sunlitght.Direction = Vector3(1, 0, 0.5);
		sunlitght.Color = Color(0.5, 0.5, 0);

		Vector3 CameraPos = Vector3(0, 0.5, 2);
		Vector3 center(0, 0, 0);	//相机朝向原点
		Vector3 up(0, 1, 0);		//相机向上

		Matrix model(4, 4, {
			1,0,0,0,
			0,1,0,0,
			0,0,1,0,
			0,0,0,1,
			});

		Matrix view = LookAt(CameraPos, center, up);

		Matrix perspective = Perspective(1, 1, 1, 3);

		Matrix orthographic = Orthographic(1.5, 1.5, 0.5, 10);

		Matrix viewPoint = Viewport(0, 0, gameWidth, gameHeight);

		GouraudShader shader;
		shader.SetModel(model);
		shader.SetView(view);
		shader.SetProjection(perspective);
		shader.SetViewPoint(viewPoint);
	
		for (int i = 0; i < testCharacter.meshes[0].indices.size(); i += 3)
		{
			int  index1 = testCharacter.meshes[0].indices[i];
			int  index2 = testCharacter.meshes[0].indices[i + 1];
			int  index3 = testCharacter.meshes[0].indices[i + 2];

			Vector3 v1 = Vector3(testCharacter.meshes[0].vertices[index1].Position);
			Vector3 v2 = Vector3(testCharacter.meshes[0].vertices[index2].Position);
			Vector3 v3 = Vector3(testCharacter.meshes[0].vertices[index3].Position);

			int len = gameWidth * gameHeight;
			int* zbuffer = new int[len];

			for (int inedx = 0; inedx < len; inedx++)
			{
				zbuffer[inedx] = 10000000;
			}

			auto sv1 = shader.Vertex(v1);  
			auto sv2 = shader.Vertex(v2);
			auto sv3 = shader.Vertex(v3);

			fillTriangleFromEdgeWitchZbuffer(
				sv1, sv2, sv3,
				image, red, zbuffer);
		}

		//-----step 3 projection
		//  |a b| |x|  =>|ax + by|
		//	|c d| |y|    |cx + dy|
		//

		//Matrix S(3, 3,
		//	{
		//		2,0,0,
		//		0,1,0,
		//		0,0,2
		//	});

		//Matrix T(3, 3,
		//	{
		//		1,0,4,
		//		0,1,5,
		//		0,0,1
		//	});
		//std::cout << S << std::endl;
		//std::cout << T << std::endl;
		//auto st = S * T;
		//std::cout << st << std::endl;
		//auto ts = T * S;
		//std::cout << ts << std::endl;

		//Vector2 square[4] = { Vector2(60,60),Vector2(60,360), Vector2(360,360),Vector2(360,60) };
		//for (int i = 0; i < 4; i++)
		//{
		//	line(square[i % 4], square[(i + 1) % 4], image, red);
		//}

		//const double pi = std::acos(-1);

		//for (int i = 0; i < 4; i++)
		//{
		//	Matrix mat1(3, 3,
		//		{
		//			1, 0,0,
		//			0, 1,0,
		//			0.2,0,1
		//		});

		//	Matrix mat2(3, 1,
		//		{
		//			square[i].x,
		//			square[i].y,
		//			1
		//		});

		//	Matrix result = mat1 * mat2;
		//	std::cout << result << std::endl;
		//	float x = result[0][0] / result[2][0];
		//	float y = result[1][0] / result[2][0];
		//	square[i] = Vector2(x, y);
		//}

		//Matrix mat1(2, 2, { (float)std::cos(pi / 5), (float)-std::sin(pi / 8),(float)std::sin(pi / 8), (float)std::cos(pi / 8) });

		//for (int i = 0; i < 4; i++)
		//{
		//	Matrix mat2(2, 1, { square[i].x ,square[i].y });
		//	Matrix result = mat1 * mat2;
		//	square[i] = Vector2(result[0][0], result[1][0]);
		//
		//}

		//for (int i = 0; i < 4; i++)
		//{
		//	line(square[i % 4], square[(i + 1) % 4], image, blue);
		//}

		image.flip_horizontally();

		unsigned char* data = image.buffer();
		width = image.get_width();
		height = image.get_height();
		nrChannels = image.get_bytespp();

		if (data)
		{
			try
			{
				if (nrChannels == 4)
				{
					glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
				}
				else if (nrChannels == 3)
				{
					glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
				}
				else if (nrChannels == 1)
				{
					glTexImage2D(GL_TEXTURE_2D, 0, GL_RED, width, height, 0, GL_RED, GL_UNSIGNED_BYTE, data);
				}
				else
				{
					int c = nrChannels;
				}

				glGenerateMipmap(GL_TEXTURE_2D);
			}
			catch (const std::exception&)
			{
			}
		}
		else
		{
			std::cout << "Failed to load texture" << std::endl;
		}

		image.clear();
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

	Vector2 Matirx2x2(Vector2 p, float a, float b, float c, float d)
	{
		return Vector2(a * p.x + b * p.y, c * p.x + d * p.y);
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

	void fillTriangleFromEdgeWitchZbuffer(Vector3 t0, Vector3 t1, Vector3 t2, TGAImage& image, TGAColor color, int* zbuffer)
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
					if (P.x >= 0 && P.y >= 0 && P.x <= gameWidth && P.y <= gameHeight)
					{
						int cacheDeep = zbuffer[int(x + y * gameWidth)];
						if (P.z < cacheDeep)
						{
							image.set(P.x, P.y, col);
							zbuffer[int(x + y * gameWidth)] = P.z;
						}
						else
						{
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
}