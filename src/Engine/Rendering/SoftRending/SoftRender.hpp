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
#include "Core/Math//Determinant.h"
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
		unsigned int depthID = 0;
		unsigned int sceneID = 0;

		int frameWidth = 500;
		int frameHeight = 500;
		ILight* sunlitght = nullptr;
		Model character;
		Camera MainCamera;
		Camera EditorCamera;

		//---------- Simulate  VRAM    Data
		vector<Primitive> primitiveDatas;

		//---------- Simulate  VRAM    Data

		//if we use opegl, we need to load data ;  mesh , texture , shader and
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
			((DirectLight*)sunlitght)->Direction = Vector3(-1, -2, 0);
			((DirectLight*)sunlitght)->Color = TMColor(0.5, 0.5, 0);

			MainCamera.position = Vector3(0, 2, 1);
			MainCamera.center = Vector3(0, 2, 0);
			MainCamera.up = Vector3(0, 1, 0);

			TGAImage depth(frameWidth, frameHeight, TGAImage::RGB);
			//around the Y axis rotate 180
			Matrix model(4, 4, {
				cos(180.0f / 360 * 2 * Pi),0,sin(180.0f / 360 * 2 * Pi),0,
				0,1,0,0,
				-sin(180.0f / 360 * 2 * Pi),0,cos(180.0f / 360 * 2 * Pi),0,
				0,0,0,1,
				});

			Matrix view = MainCamera.LookAt();

			Matrix perspective = MainCamera.Perspective(1, 1, 1, 3);

			Matrix orthographic = MainCamera.Orthographic(2, 2, 0, 5);

			Matrix viewPoint = MainCamera.Viewport(0, 0, frameWidth, frameHeight);

			int len = frameWidth * frameHeight;
			int* zbuffer = new int[len];
			int* shadowbuffer = new int[len];
			int* editorZbuffer = new int[len];

			for (int inedx = 0; inedx < len; inedx++)
			{
				shadowbuffer[inedx] = INT_MAX;
				zbuffer[inedx] = INT_MAX;
				editorZbuffer[inedx] = INT_MAX;
			}

			Debug::Log("------Start------Rasterizer Stage------------------------------------\n");

			ITexture* mainTex, * normalMap ,* specularTex;
			mainTex = new OpenGLTexture();
			normalMap = new OpenGLTexture();
			specularTex = new OpenGLTexture();
			string mainPath = FileSystem::getPath("resources/objects/cyborg") + '/' + string("cyborg_diffuse.tga");
			string normalPath = FileSystem::getPath("resources/objects/cyborg") + '/' + string("cyborg_normal.tga");
			string specularPath = FileSystem::getPath("resources/objects/cyborg") + '/' + string("cyborg_specular.tga");
			mainTex->image = mainTex->LoadTGATexture(mainPath.c_str());
			normalMap->image = normalMap->LoadTGATexture(normalPath.c_str());
			specularTex->image = specularTex->LoadTGATexture(specularPath.c_str());
			vector<ITexture*> modelTextures;
			modelTextures.push_back(mainTex);
			modelTextures.push_back(normalMap);
			modelTextures.push_back(specularTex);

			IShader* depthShader = new DepthShader();
			depthShader->light = sunlitght;
			view = MainCamera.LookAt(Vector3(1, 4, 0), Vector3(0, 2, 0), MainCamera.up);

			Matrix objectToShadowScreen = viewPoint * orthographic * view * model;

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
			depth.write_tga_file(FileSystem::getPath("depth.tga").c_str());
			depth.flip_horizontally();
			depth.flip_vertically();  // reture normal
			;

			LoadAssetToMemory();
			view = MainCamera.LookAt(MainCamera.position, MainCamera.center, MainCamera.up);
			Matrix object2GameScreen = viewPoint * orthographic * view * model; 
			Matrix  gameScreen2Object = object2GameScreen.Inverse(); // revert the transform 
			TGAImage frame(frameWidth, frameHeight, TGAImage::RGB); 
			IShader* gouraudShader = new GouraudShader();
			gouraudShader->textures = modelTextures;
			gouraudShader->light = sunlitght;

			((GouraudShader*)gouraudShader)->shadowbuffer = shadowbuffer;
			((GouraudShader*)gouraudShader)->object2ShadowScreen = objectToShadowScreen;
			((GouraudShader*)gouraudShader)->frameScreen2Object = gameScreen2Object;
			((GouraudShader*)gouraudShader)->screenWidth = frameWidth;
			((GouraudShader*)gouraudShader)->screenHeight = frameHeight;

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

				fillTriangleUseClip(
					viewPoint,
					primitiveDatas[i].poins[0],
					primitiveDatas[i].poins[1],
					primitiveDatas[i].poins[2],
					frameWidth, frameHeight,
					frame, red, zbuffer, sunlitght, primitiveDatas[i].shader);
			}

			frame.flip_horizontally();
			frame.flip_vertically();
			frame.write_tga_file(FileSystem::getPath("frame.tga").c_str());
			frame.flip_horizontally();
			frame.flip_vertically();
			frame.flip_RGBA();   // exchange the  R and B ,the tga format is different with opengl texture data

			LoadAssetToMemory();
			TGAImage scene(frameWidth, frameHeight, TGAImage::RGB);
			EditorCamera.position = Vector3(5, 2, 0);
			EditorCamera.center = Vector3(0, 2, 0);
			EditorCamera.up = Vector3(0, 1, 0);
			view = EditorCamera.LookAt(EditorCamera.position, EditorCamera.center, EditorCamera.up);
			orthographic = EditorCamera.Orthographic(2, 2, 0, 7);

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

				if (primitiveDatas[i].primitiveType == PrimitiveType::TRIANGLES)
				{
					fillTriangleFromEdgeWitchZbuffer(
						primitiveDatas[i].poins[0],
						primitiveDatas[i].poins[1],
						primitiveDatas[i].poins[2],
						frameWidth, frameHeight,
						scene, red, editorZbuffer, sunlitght, primitiveDatas[i].shader);
				}
				else if (primitiveDatas[i].primitiveType == PrimitiveType::POINTS)
				{
				}
			}

			IVertex c1, c2, c3, c4, c5, c6, c7, c8;
			float dist = 0.15f;
			c1.Position = MainCamera.position + Vector3(0.5f, 0.5f, 0.5f) * dist;
			c2.Position = MainCamera.position + Vector3(0.5f, 0.5f, -0.5f) * dist;
			c3.Position = MainCamera.position + Vector3(0.5f, -0.5f, -0.5f) * dist;
			c4.Position = MainCamera.position + Vector3(0.5f, -0.5f, 0.5f) * dist;
			c5.Position = MainCamera.position + Vector3(-0.5f, -0.5f, 0.5f) * dist;
			c6.Position = MainCamera.position + Vector3(-0.5f, 0.5f, 0.5f) * dist;
			c7.Position = MainCamera.position + Vector3(-0.5f, 0.5f, -0.5f) * dist;
			c8.Position = MainCamera.position + Vector3(-0.5f, -0.5f, -0.5f) * dist;
			primitiveDatas.clear();
			primitiveDatas.push_back(Primitive(PrimitiveType::TRIANGLES, vector<IVertex>({ c1,c2,c3 })));
			primitiveDatas.push_back(Primitive(PrimitiveType::TRIANGLES, vector<IVertex>({ c1,c3,c4 })));

			primitiveDatas.push_back(Primitive(PrimitiveType::TRIANGLES, vector<IVertex>({ c1,c4,c5 })));
			primitiveDatas.push_back(Primitive(PrimitiveType::TRIANGLES, vector<IVertex>({ c1,c5,c6 })));

			primitiveDatas.push_back(Primitive(PrimitiveType::TRIANGLES, vector<IVertex>({ c1,c6,c7 })));
			primitiveDatas.push_back(Primitive(PrimitiveType::TRIANGLES, vector<IVertex>({ c1,c7,c2 })));

			primitiveDatas.push_back(Primitive(PrimitiveType::TRIANGLES, vector<IVertex>({ c8,c7,c6 })));
			primitiveDatas.push_back(Primitive(PrimitiveType::TRIANGLES, vector<IVertex>({ c8,c6,c5 })));

			primitiveDatas.push_back(Primitive(PrimitiveType::TRIANGLES, vector<IVertex>({ c8,c5,c4 })));
			primitiveDatas.push_back(Primitive(PrimitiveType::TRIANGLES, vector<IVertex>({ c8,c4,c3 })));

			primitiveDatas.push_back(Primitive(PrimitiveType::TRIANGLES, vector<IVertex>({ c8,c3,c2 })));
			primitiveDatas.push_back(Primitive(PrimitiveType::TRIANGLES, vector<IVertex>({ c8,c2,c7 })));
			model = Matrix(4, 4,
				{
				1,0,0,0,
				0,1,0,0,
				0,0,1,0,
				0,0,0,1,
				});

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

				if (primitiveDatas[i].primitiveType == PrimitiveType::TRIANGLES)
				{
					fillTriangleFromEdgeWitchZbuffer(
						primitiveDatas[i].poins[0],
						primitiveDatas[i].poins[1],
						primitiveDatas[i].poins[2],
						frameWidth, frameHeight,
						scene, red, editorZbuffer, sunlitght, primitiveDatas[i].shader);
				}if (primitiveDatas[i].primitiveType == PrimitiveType::POINTS)
				{
				}
			}

			scene.flip_horizontally();
			scene.flip_vertically();
			scene.write_tga_file(FileSystem::getPath("scene.tga").c_str());
			scene.flip_horizontally();
			scene.flip_vertically();
			scene.flip_RGBA();   // exchange the  R and B ,the tga format is different with opengl texture data

			ITexture* tga2Opengl = new OpenGLTexture();
			frameID = tga2Opengl->TGA2GLTexture(frame);
			depthID = tga2Opengl->TGA2GLTexture(depth);
			sceneID = tga2Opengl->TGA2GLTexture(scene);
			depth.clear();
			frame.clear();
		}
	};
} //namespace TmingEngine

#endif //TmingEngine_Engine_Rending_SoftRender_hpp_