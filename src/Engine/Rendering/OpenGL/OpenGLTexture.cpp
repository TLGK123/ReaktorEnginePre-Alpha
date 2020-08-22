/*
All code samples, unless explicitly stated otherwise,
are licensed under the terms of the CC BY - NC 4.0 license as published by Creative Commons,
either version 4 of the License, or (at your option) any later version.
//See https ://learnopengl.com/About for more information.
*/

//#include "im.h"

#include<iostream>
#include "OpenGLTexture.hpp"

#define STB_LIB_IMPLEMENTATION
#include "Stb_Image/stb_image.h"

namespace TmingEngine
{
	unsigned int OpenGLTexture::LoadTexture(const char* path)

	{
		string filename = string(path);
		unsigned int textureID;
		glGenTextures(1, &textureID);

		int width, height, nrComponents;
		unsigned char* data = stbi_load(filename.c_str(), &width, &height, &nrComponents, 0);
		if (data)
		{
			GLenum format;
			if (nrComponents == 1)
				format = GL_RED;
			else if (nrComponents == 3)
				format = GL_RGB;
			else if (nrComponents == 4)
				format = GL_RGBA;

			glBindTexture(GL_TEXTURE_2D, textureID);
			glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
			glGenerateMipmap(GL_TEXTURE_2D);

			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

			stbi_image_free(data);
		}
		else
		{
			std::cout << "Texture failed to load at path: " << path << std::endl;
			stbi_image_free(data);
		}

		return textureID;
	}

	TGAImage OpenGLTexture::LoadTGATexture(const char* path)
	{
		TGAImage image;
		string filename = string(path);
		//int width, height, channel;
		//unsigned char* data = stbi_load(filename.c_str(), &width, &height, &channel, 0);
		//if (data)
		//{
		//	image.data = data;
		//	image.width = width;
		//	image.height = height;
		//	image.bytespp = channel;
		//}
		//else
		//{
		//	std::cout << "Texture failed to load at path: " << path << std::endl;
		//	stbi_image_free(data);
		//}
		image.read_tga_file(filename.c_str());
		//image.flip_horizontally();
		image.flip_vertically();

		//string wf = filename + ".tga";
		//image.write_tga_file(wf.c_str());

		return image;
	}
}