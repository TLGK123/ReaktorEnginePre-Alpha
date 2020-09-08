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
#include "Core/SubSystem.h"
#include "Plantform/File/FileSystem.h"

#include "Rendering/OpenGL/OpenGLModel.hpp"
#include "Rendering/SoftRending/Primitive.hpp"
#include "Rendering/SoftRending/GouraudShader.hpp"
#include "Rendering/SoftRending/DepthShader.hpp"
#include "Rendering/SoftRending/SoftGL.hpp"
#include "Rendering/TMColor.hpp"
#include "Rendering/Light.hpp"
#include "Rendering/Camera.hpp"

namespace TmingEngine
{
	ENGINE_CLASS class SoftRender : public Subsystem
	{
	public:
		SoftRender(Context* context) : Subsystem(context) {};

		~SoftRender() {};

		unsigned int frameID = 0;

		int frameWidth = 640;
		int frameHeight = 640;
		ILight* sunlitght;
		Model character;
		Camera camera;

		//---------- Simulate  VRAM    Data
		vector<Primitive> primitiveDatas;

		//---------- Simulate  VRAM    Data

		//if we use opegl, we need to load data that like mesh , texture and
		//so on to the VRAM (Vedio Random Access Memory)
		void LoadAssetToMemory()
		{
			character.Init(FileSystem::getPath("resources/objects/cyborg/cyborg.obj"));
			primitiveDatas.clear();
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
		}

		// spicify the Texture , vertex shader ,fragment shader for each Primitive
		void SetRenderStatus()
		{
		}

		void DrawCall()
		{
			Debug::Log("------Start------Geometry Stage------------------------------------\n");
			GenerateFrames();
		}

	private:
		// generate one frame mean that we will make one picture ,
		// if we change the picture at the main thread update ,
		// we will get a consecutive game scene
		//
		void GenerateFrames()
		{
			sunlitght = new DirectLight();
			((DirectLight*)sunlitght)->Direction = Vector3(0, -2, -1);
			((DirectLight*)sunlitght)->Color = TMColor(0.5, 0.5, 0);

			camera.position = Vector3(0, 2, 1);
			camera.center = Vector3(0, 2, 0);
			camera.up = Vector3(0, 1, 0);

			TGAImage depth(frameWidth, frameHeight, TGAImage::RGB);
			//around the Y axis rotate 180
			Matrix model(4, 4, {
				cos(85.0f / 360 * 2 * Pi),0,sin(85.0f / 360 * 2 * Pi),0,
				0,1,0,0,
				-sin(85.0f / 360 * 2 * Pi),0,cos(85.0f / 360 * 2 * Pi),0,
				0,0,0,1,
				});

			Matrix view = camera.LookAt();

			Matrix perspective = camera.Perspective(1, 1, 1, 3);

			Matrix orthographic = camera.Orthographic(2, 2, 0, 5);

			Matrix viewPoint = camera.Viewport(0, 0, frameWidth, frameHeight);

			int len = frameWidth * frameHeight;
			int* zbuffer = new int[len];
			int* shadowbuffer = new int[len];

			for (int inedx = 0; inedx < len; inedx++)
			{
				shadowbuffer[inedx] = 10000000;
				zbuffer[inedx] = 10000000;
			}

			Debug::Log("------Start------Rasterizer Stage------------------------------------\n");

			ITexture* mainTex, * normalMap;
			mainTex = new OpenGLTexture();
			normalMap = new OpenGLTexture();
			string path = FileSystem::getPath("resources/objects/cyborg") + '/' + string("cyborg_diffuse.tga");
			mainTex->image = mainTex->LoadTGATexture(path.c_str());
			normalMap->image = normalMap->LoadTGATexture(path.c_str());
			vector<ITexture*> modelTextures;
			modelTextures.push_back(mainTex);
			modelTextures.push_back(normalMap);

			IShader* depthShader = new DepthShader();
			depthShader->textures = modelTextures;
			depthShader->light = sunlitght;
			view = camera.LookAt(Vector3(0, 2, 1), camera.center, camera.up);
			for (int i = 0; i < primitiveDatas.size(); i++)
			{
				primitiveDatas[i].shader = depthShader;
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
					depth, red, shadowbuffer, sunlitght, primitiveDatas[i].shader);
			}
			depth.flip_horizontally();
			depth.flip_vertically();  //for write to disk
			depth.write_tga_file(string("E:/WorkSpace/Giteet/TmingEngine/depth.tga").c_str());
			depth.flip_vertically();  // reture normal
			;

			LoadAssetToMemory();
			TGAImage frame(frameWidth, frameHeight, TGAImage::RGB);
			IShader* gouraudShader = new GouraudShader();
			gouraudShader->textures = modelTextures;
			gouraudShader->light = sunlitght;
			view = camera.LookAt(camera.position, camera.center, camera.up);
			for (int i = 0; i < primitiveDatas.size(); i++)
			{
				primitiveDatas[i].shader = gouraudShader;
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
					frame, red, zbuffer, sunlitght, primitiveDatas[i].shader);
			}

			frame.flip_horizontally();
			frame.flip_vertically();
			frame.write_tga_file(string("E:/WorkSpace/Giteet/TmingEngine/frame.tga").c_str());
			frame.flip_vertically();
			frame.flip_RGBA();   // exchange the  R and B ,the tga format is different with opengl texture data

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

			unsigned char* data = frame.buffer(); // directly set the opengl texture data with tag imgae data
			nrChannels = frame.get_bytespp();

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

			depth.clear();
			frame.clear();
		}
	};
} //namespace TmingEngine

#endif //TmingEngine_Engine_Rending_SoftRender_hpp_