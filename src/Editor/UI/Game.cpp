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
		gameWidth = 500;
		gameHeight = 500;
		SoftRender();
	}

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

		Vector2 t0[3] = { Vector2(40, 40),   Vector2(350, 100),  Vector2(250, 300) };
		Vector2 t1[3] = { Vector2(180, 50),  Vector2(150, 1),   Vector2(70, 180) };
		Vector2 t2[3] = { Vector2(180, 350), Vector2(120, 260), Vector2(130, 400) };
		triangle(t0[0], t0[1], t0[2], image, red);
		fillTriangle(t0[0], t0[1], t0[2], image, red);

		triangle(t1[0], t1[1], t1[2], image, blue);
		fillTriangle(t1[0], t1[1], t1[2], image, blue);

		triangle(t2[0], t2[1], t2[2], image, green);
		fillTriangleFromEdge(t2[0], t2[1], t2[2], image, green);

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
		Vector2* boxs = findTriangleBox(A,B,C);
		Vector2 minPoint = boxs[0];
		Vector2 maxPoint = boxs[1];
		drawBox(minPoint, maxPoint,image,color);
		for (int y = minPoint.y ; y <=  maxPoint.y; y++)
		{
			for (int x = minPoint.x; x <= maxPoint.x; x++)
			{
				Vector2 P = Vector2(x,y);

				Vector2 ab = B - A; //向量 AB
				Vector2 ap = P - A; //向量 AP

				Vector2 bc = Vector2(C.x - B.x, C.y - B.y); //向量 BC
				Vector2 bp = Vector2(P.x - B.x, P.y - B.y); //向量 BP

				Vector2 ca = Vector2(A.x - C.x, A.y - C.y); //向量 CA
				Vector2 cp = Vector2(P.x - C.x, P.y - C.y); //向量 CP

				float fabp = ab.x * ap.y - ap.x * ab.y;
				float fbcp = bc.x * bp.y - bp.x * bc.y;
				float fcap = ca.x * cp.y - cp.x * ca.y;

				if (fabp>=0 && fbcp >= 0 && fcap >=0)
				{
					image.set(x, y, color);
				}
			}
		}
	}

	void fillTriangle(Vector2 t0, Vector2 t1, Vector2 t2, TGAImage& image, TGAColor color)
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

		drawBox(b1,b2,image,color);
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

	
}