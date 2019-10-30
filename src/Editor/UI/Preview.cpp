//
//
//

#include "Preview.hpp"
#include <Stb_Image\stb_image.h>
TmingEngine::Preview::~Preview()
{
}

void TmingEngine::Preview::Begin()
{
	p_open = true;
}

void TmingEngine::Preview::Update()
{
	if (!p_open)
	{
		return;
	}
    ImGui::SetNextWindowSize(ImVec2(640, 360), ImGuiCond_FirstUseEver);
    if (!ImGui::Begin("Preview", &p_open))
    {
        ImGui::End();
        return;
    }
    ImTextureID my_tex_id = (void *)ImageId;
    float my_tex_w = ImGui::GetWindowSize().x-35;
    float my_tex_h = ImGui::GetWindowSize().y-35;
    //----------------------------------------------------------------- -1 -1  Image reversal

	ImGui::Image(my_tex_id, ImVec2(my_tex_w, my_tex_h), ImVec2(0, 0), ImVec2(-1, -1), ImColor(255, 255, 255, 255), ImColor(255, 255, 255, 128));	
	ImGui::End();
}

void TmingEngine::Preview::End()
{
}

void TmingEngine::Preview::PreviewTexture(string path)
{
	Debug::Log("open path"+ path+"\n");
	
	glGenTextures(1, &texture1);

	glBindTexture(GL_TEXTURE_2D, texture1);
	// set the texture wrapping parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	// set texture wrapping to GL_REPEAT (default wrapping method)
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	// set texture filtering parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	//// load image, create texture and generate mipmaps
	int width, height, nrChannels;

	stbi_set_flip_vertically_on_load(true); // tell stb_image.h to flip loaded texture's on the y-axis.

	unsigned char* data = stbi_load(path.c_str(), &width, &height, &nrChannels, 0);
	if (data)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
		std::cout << "Failed to load texture" << std::endl;
	}
	stbi_image_free(data);
	ImageId = texture1;
}
