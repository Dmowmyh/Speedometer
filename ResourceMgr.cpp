#include "ResourceMgr.h"
#include <GL/glew.h>
#include <GL/glut.h>
#include <iostream>

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

bool ResourceMgr::LoadResource(const std::string& name)
{
	/*glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	// set texture wrapping to GL_REPEAT (default wrapping method)
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR)*/;
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	stbi_set_flip_vertically_on_load(true);
	unsigned int textureID;
	glGenTextures(1, &textureID); 
	glBindTexture(GL_TEXTURE_2D, textureID);
	int width, height, nrChannel;
	std::string resourcePath = "data/" + name;
	unsigned char* data = stbi_load(resourcePath.c_str(), &width, &height,
			&nrChannel, STBI_rgb_alpha);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0,
			GL_RGBA, GL_UNSIGNED_BYTE, data);
	if (data == nullptr)
	{
		std::cout << "FAILED TO LOAD " << resourcePath << std::endl;
		return false;
	}
	glGenerateMipmap(GL_TEXTURE_2D);
	stbi_image_free(data);
	m_Textures.insert(std::make_pair(name, textureID));
	return true;
}

unsigned int ResourceMgr::GetResourceID(const std::string& name)
{
	if (m_Textures.find(name) != m_Textures.end())
	{
		return m_Textures.find(name)->second;	
	}
	return 0;
}
