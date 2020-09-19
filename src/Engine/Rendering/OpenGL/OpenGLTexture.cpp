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
		std::string filename = std::string(path);
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
		std::string filename = std::string(path);
		image.read_tga_file(filename.c_str());
		image.flip_vertically();
		return image;
	}

	unsigned int OpenGLTexture::TGA2GLTexture(TGAImage image)
	{
		unsigned int imageID;
		int frameWidth = image.get_width();
		int frameHeight = image.get_height();
		glGenTextures(1, &imageID);

		glBindTexture(GL_TEXTURE_2D, imageID);
		// set the texture wrapping parameters
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		// set texture wrapping to GL_REPEAT (default wrapping method)
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		// set texture filtering parameters
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		//// load image, create texture and generate mipmaps
		int nrChannels;

		unsigned char* data = image.buffer(); // directly set the opengl texture data with tag imgae data
		nrChannels = image.get_bytespp();

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

		return imageID;
	}
}