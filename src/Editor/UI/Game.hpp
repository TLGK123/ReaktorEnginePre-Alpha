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
		int gameWidth;
		int gameHeight;
	};

	const TGAColor white = TGAColor(255, 255, 255, 255);
	const TGAColor red = TGAColor(255, 0, 0, 255);
	const TGAColor green = TGAColor(0, 255, 0, 255);
	const TGAColor blue = TGAColor(0, 0, 255, 255);

	void fillTriangle(ImVec2 t0, ImVec2 t1, ImVec2 t2, TGAImage& image, TGAColor color); //填充一个普通三角形
	void fillUpTriangle(ImVec2 t0, ImVec2 t1, ImVec2 t2, TGAImage& image, TGAColor color); //填充一个底边平行 X 轴 ，顶点在上的三角形
	void fillDownTriangle(ImVec2 t0, ImVec2 t1, ImVec2 t2, TGAImage& image, TGAColor color);//填充一个底边平行 X 轴 ，顶点在下的三角形
}

#endif /* Game_hpp */