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

#include "Rendering/OpenGL/OpenGLModel.hpp"
#include "Rendering/SoftRending/Primitive.hpp"
#include "Rendering/SoftRending/GouraudShader.hpp"
#include "Rendering/SoftRending/DepthShader.hpp"
#include "Rendering/SoftRending/SoftGL.hpp"
#include "Rendering/TMColor.hpp"
#include "Rendering/Light.hpp"

namespace TmingEngine
{
	ENGINE_CLASS class SoftRender
	{
	public:
		SoftRender() {};
		~SoftRender() {};

		unsigned int frameID = 0;

		int frameWidth = 640;
		int frameHeight = 640;
		ILight* sunlitght;
		Model character;
		Vector3 CameraPos = Vector3(0, 2, 1);
		Vector3 center = Vector3(0, 2, 0);	//相机朝向原点
		Vector3 up = Vector3(0, 1, 0);		//相机向上

		//---------- Simulate  VRAM    Data
		vector<Primitive> primitiveDatas;

		//---------- Simulate  VRAM    Data

		//if we use opegl, we need to load data that like mesh , texture and
		//so on to the VRAM (Vedio Random Access Memory)
		void LoadAssetToMemory()
		{
			character.Init(FileSystem::getPath("resources/objects/cyborg/cyborg.obj"));
			for (int i = 0; i < character.meshes[0]->indices.size(); i += 3)
			{
				int  index1 = character.meshes[0]->indices[i];
				int  index2 = character.meshes[0]->indices[i + 1];
				int  index3 = character.meshes[0]->indices[i + 2];

				IVertex v1 = (character.meshes[0]->vertices[index1]);
				IVertex v2 = (character.meshes[0]->vertices[index2]);
				IVertex v3 = (character.meshes[0]->vertices[index3]);

				Primitive primitive(PrimitiveType::TRIANGLES, vector<IVertex>({ v1,v2,v3 }));

				primitiveDatas.push_back(primitive);
			}

			//Vertex v1, v2, v3;
			//v1.Position = Vector3(0, 0, 0);
			//v1.TexCoords = Vector2(0, 0);

			//v2.Position = Vector3(0, 1, 0);
			//v2.TexCoords = Vector2(0, 1);

			//v3.Position = Vector3(1, 0, 0);
			//v3.TexCoords = Vector2(1, 0);

			//Primitive primitive(PrimitiveType::TRIANGLES, vector<Vertex>({ v1,v2,v3 }));

			//Vertex v11, v12, v13;
			//v11.Position = Vector3(-1, -1, 0);
			//v11.TexCoords = Vector2(0, 0);

			//v12.Position = Vector3(-1, 1, 0);
			//v12.TexCoords = Vector2(0, 1);

			//v13.Position = Vector3(1, -1, 0);
			//v13.TexCoords = Vector2(1, 0);

			//Primitive primitive2(PrimitiveType::TRIANGLES, vector<Vertex>({ v11,v12,v13 }));

			////primitiveDatas.push_back(primitive);
			//primitiveDatas.push_back(primitive2);
		}

		// spicify the Texture , vertex shader ,fragment shader for each Primitive
		void SetRenderStatus()
		{
			sunlitght = new DirectLight();
			((DirectLight*)sunlitght)->Direction = Vector3(0, 0, -3);
			((DirectLight*)sunlitght)->Color = TMColor(0.5, 0.5, 0);

			IShader* shader = new GouraudShader();
			//shader->textures = character.textures_loaded;

			shader->light = sunlitght;

			vector<ITexture*> modelTextures;
			ITexture* mainTex, * normalMap;
			mainTex = new OpenGLTexture();
			normalMap = new OpenGLTexture();

			string path = FileSystem::getPath("resources/objects/cyborg") + '/' + string("cyborg_diffuse.tga");
			mainTex->image = mainTex->LoadTGATexture(path.c_str());
			normalMap->image = normalMap->LoadTGATexture(path.c_str());

			modelTextures.push_back(mainTex);
			modelTextures.push_back(normalMap);

			shader->textures = modelTextures;
			for (int i = 0; i < primitiveDatas.size(); i++)
			{
				primitiveDatas[i].shader = shader;
			}
		}

		void DrawCall()
		{
			Debug::Log("------Start------Geometry Stage------------------------------------\n");
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
			int nrChannels;

			TGAImage image(frameWidth, frameHeight, TGAImage::RGB);

			//around the Y axis rotate 180
			Matrix model(4, 4, {
				cos(180.0f / 360 * 2 * Pi),0,sin(180.0f / 360 * 2 * Pi),0,
				0,1,0,0,
				-sin(180.0f / 360 * 2 * Pi),0,cos(180.0f / 360 * 2 * Pi),0,
				0,0,0,1,
				});

			Matrix view = LookAt(CameraPos, center, up);

			Matrix perspective = Perspective(1, 1, 1, 3);

			Matrix orthographic = Orthographic(2, 2, 0, 5);

			Matrix viewPoint = Viewport(0, 0, frameWidth, frameHeight);

			//std::cout << view << std::endl;

			int len = frameWidth * frameHeight;
			int* zbuffer = new int[len];

			for (int inedx = 0; inedx < len; inedx++)
			{
				zbuffer[inedx] = 10000000;
			}

			Debug::Log("------Start------Rasterizer Stage------------------------------------\n");

			for (int i = 0; i < primitiveDatas.size(); i++)
			{
				primitiveDatas[i].shader->SetModel(model);
				primitiveDatas[i].shader->SetView(view);
				primitiveDatas[i].shader->SetProjection(orthographic);
				primitiveDatas[i].shader->SetViewPoint(viewPoint);

				primitiveDatas[i].VertexShader();               //run the vertex shader for each point in a primitive
				primitiveDatas[i].TessellationShader();			//run the tessellation shader for a primitive
				primitiveDatas[i].GeometryShader();				//run the geometry shader for a primitive

				fillTriangleFromEdgeWitchZbuffer(
					primitiveDatas[i].poins[0],
					primitiveDatas[i].poins[1],
					primitiveDatas[i].poins[2],
					frameWidth, frameHeight,
					image, red, zbuffer, sunlitght, primitiveDatas[i].shader);

				//	triangle(primitiveDatas[i].poins[0],
				//	primitiveDatas[i].poins[1],
				//	primitiveDatas[i].poins[2], image, red);
			}

			image.flip_horizontally();
			//image.write_tga_file(string("E:/WorkSpace/Giteet/TmingEngine/1.tga").c_str());

			image.flip_RGBA();   // exchange the  R and B ,the tga format is different with opengl texture data
			unsigned char* data = image.buffer(); // directly set the opengl texture data with tag imgae data
			nrChannels = image.get_bytespp();

			if (data)
			{
				try
				{
					if (nrChannels == 4)
					{
						glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, frameWidth, frameHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
					}
					else if (nrChannels == 3)
					{
						glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, frameWidth, frameHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
					}
					else if (nrChannels == 1)
					{
						glTexImage2D(GL_TEXTURE_2D, 0, GL_RED, frameWidth, frameHeight, 0, GL_RED, GL_UNSIGNED_BYTE, data);
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