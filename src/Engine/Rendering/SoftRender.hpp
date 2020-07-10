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

#ifndef TmingEngine_Engine_Rending_SoftRender_hpp_
#define TmingEngine_Engine_Rending_SoftRender_hpp_

#include "Core/EngineDefs.h"
#include "Plantform/FileSystem/FileSystem.h"
#include "Rendering/Model.hpp"
#include "Rendering/Primitive.hpp"
#include "Rendering/GouraudShader.hpp"
#include "Rendering/Color.hpp"
#include "Rendering/Light.hpp"
#include "Rendering/SoftGL.hpp"

namespace TmingEngine
{
	ENGINE_CLASS class SoftRender
	{
	public:
		SoftRender() {};
		~SoftRender() {};

		static unsigned int frameID;

		static int frameWidth;
		static int frameHeight;
		Light sunlitght;

		//---------- Simulate  VRAM    Data
		vector<Primitive> primitiveDatas;

		//---------- Simulate  VRAM    Data

		//if we use opegl, we need to load data that like mesh , texture and
		//so on to the VRAM (Vedio Random Access Memory)
		void LoadAssetToMemory()
		{
			Model character(FileSystem::getPath("resources/objects/rock/rock.obj"));
			for (int i = 0; i < character.meshes[0].indices.size(); i += 3)
			{
				int  index1 = character.meshes[0].indices[i];
				int  index2 = character.meshes[0].indices[i + 1];
				int  index3 = character.meshes[0].indices[i + 2];

				Vertex v1 = (character.meshes[0].vertices[index1]);
				Vertex v2 = (character.meshes[0].vertices[index2]);
				Vertex v3 = (character.meshes[0].vertices[index3]);

				Primitive primitive(PrimitiveType::TRIANGLES, vector<Vertex>({ v1,v2,v3 }));
				primitiveDatas.push_back(primitive);
			}
		}

		// spicify the Texture , vertex shader ,fragment shader for each Primitive
		void SetRenderStatus()
		{
			for (int i = 0; i < primitiveDatas.size(); i++)
			{
				primitiveDatas[i].shader = new GouraudShader();
			}
		}

		void DrawCall()
		{
			GenerateFrames();
		}

	private:
		// generate one frame mean that we will make one picture ,
		// if we change the picture at the main therad update ,
		// we will get a consecutive game scene
		//
		void GenerateFrames()
		{
			glGenTextures(1, &frameID);

			glBindTexture(GL_TEXTURE_2D, frameID);
			// set the texture wrapping parameters
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
			// set texture wrapping to GL_REPEAT (default wrapping method)
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
			// set texture filtering parameters
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
			//// load image, create texture and generate mipmaps
			int width, height, nrChannels;

			TGAImage image(frameWidth, frameHeight, TGAImage::RGB);

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

			sunlitght.Direction = Vector3(0, 1, -1);
			sunlitght.Color = Color(0.5, 0.5, 0);

			Vector3 CameraPos = Vector3(0, 1, 3);
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

			Matrix viewPoint = Viewport(0, 0, frameWidth, frameHeight);

			shader->SetModel(model);
			shader->SetView(view);
			shader->SetProjection(perspective);
			shader->SetViewPoint(viewPoint);

			int len = frameWidth * frameHeight;
			int* zbuffer = new int[len];

			for (int inedx = 0; inedx < len; inedx++)
			{
				zbuffer[inedx] = 10000000;
			}

			for (int i = 0; i < primitiveDatas.size(); i++)
			{
				fillTriangleFromEdgeWitchZbuffer(
					primitiveDatas[i].poins[0].Position,
					primitiveDatas[i].poins[1].Position,
					primitiveDatas[i].poins[2].Position,
					frameWidth, frameHeight,
					image, red, zbuffer);
			}

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
	};
} //namespace TmingEngine

#endif //TmingEngine_Engine_Rending_SoftRender_hpp_