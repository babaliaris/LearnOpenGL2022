#include "pch.h"
#include "texture.h"
#include <core/logger.h>
#include <core/gl/glcall.h>
#include <stb_image/stb_image.h>
#include <glad/glad.h>


LearnOpenGL::Texture::Texture(const std::string& path) : m_id(0), m_width(-1), m_height(-1), m_channels(0), m_path(path)
{

	//Flip the image.
	stbi_set_flip_vertically_on_load(1);

	//Try to load the image.
	unsigned char* image = stbi_load(path.c_str(), &m_width, &m_height, &m_channels, 0);

	//Image loaded successfully.
	if (image)
	{
		//Generate and bind the texture.
		GLCall(glGenTextures(1, &m_id));
		GLCall(glBindTexture(GL_TEXTURE_2D, m_id));

		//Default filters and wrappers.
		GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST));
		GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST));
		GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE));
		GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE));

		//Generate mipmaps.
		GLCall(glGenerateMipmap(GL_TEXTURE_2D));

		//Determine the correct channels for the source.
		GLenum source_channels;
		switch (m_channels)
		{
		case 1:
			source_channels = GL_R8;
			break;
		case 2:
			source_channels = GL_RG;
			break;
		case 3:
			source_channels = GL_RGB;
			break;
		case 4:
			source_channels = GL_RGBA;
			break;
		default:
			LEARN_OPENGL_ERROR("This line should never be reached. Channel numbers are: {}", m_channels);
			break;
		}

		//Load the texture into the GPU.
		GLCall(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, m_width, m_height, 0, source_channels, GL_UNSIGNED_BYTE, image));

		//Free the image from RAM.
		stbi_image_free(image);

		//Unbind the texture.
		GLCall(glBindTexture(GL_TEXTURE_2D, 0));
	}



	//Image load failed.
	else
	{
		LEARN_OPENGL_WARN("Failed to load image: {}", path.c_str());
	}
}





LearnOpenGL::Texture::~Texture()
{
	GLCall(glDeleteTextures(1, &m_id));
}





void LearnOpenGL::Texture::bind(int slot)
{
	GLCall(glActiveTexture(GL_TEXTURE0 + slot));
	GLCall(glBindTexture(GL_TEXTURE_2D, m_id));
}





void LearnOpenGL::Texture::unBind()
{
	GLCall(glBindTexture(GL_TEXTURE_2D, 0));
}
