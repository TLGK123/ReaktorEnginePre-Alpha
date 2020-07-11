/*
All code samples, unless explicitly stated otherwise,
are licensed under the terms of the CC BY - NC 4.0 license as published by Creative Commons,
either version 4 of the License, or (at your option) any later version.
//See https ://learnopengl.com/About for more information.
*/

//  Texture.h
//  TmingEngine
//

#ifndef Texture_h
#define Texture_h
#include<string>
#include "tgaimage/tgaimage.h"
using namespace std;
struct Texture {
	unsigned int id;
	string type;
	string path;
	int width;
	int height;
	TGAImage image;
};

unsigned int LoadOpenGLTextureFromFile(const char* path, const string& directory, bool gamma = false);

TGAImage LoadTGAImageFromFile(const char* path, const string& directory, bool gamma = false);

#endif /* Texture_h */