#define STB_IMAGE_IMPLEMENTATION
#include "Resource/Texture.hpp"
#include "stb_image.h"

namespace rumia
{
	Texture::Texture(const std::string& filePath) :
		m_width(0), m_height(0), m_depth(0),
		m_textureType(TextureType::Texture2D),
		Resource(filePath, ResourceType::Texture)
	{
	}

	Texture::~Texture()
	{
	}

	bool Texture::LoadProcess()
	{
		switch (m_textureType)
		{
		case TextureType::Cubemap:
			LoadCubemap();
			break;
		case TextureType::Texture1D:
			LoadTexture1D();
			break;

		case TextureType::Texture2D:
			LoadTexture2D();
			break;

		case TextureType::Texture3D:
			LoadTexture3D();
			break;
		}

		return true;
	}

	void Texture::UnloadProcess()
	{
		/* Nothing to do **/
	}

	void Texture::Bind()
	{
		switch (m_textureType)
		{
		case TextureType::Cubemap:
			glBindTexture(GL_TEXTURE_CUBE_MAP, m_id);
		case TextureType::Texture1D:
			glBindTexture(GL_TEXTURE_1D, m_id);
			break;
		case TextureType::Texture2D:
			glBindTexture(GL_TEXTURE_2D, m_id);
			break;
		case TextureType::Texture3D:
			glBindTexture(GL_TEXTURE_3D, m_id);
			break;
		}
	}

	void Texture::LoadCubemap()
	{
		//@TODO: Impl load process for Cubemap
	}

	void Texture::LoadTexture1D()
	{
		//@TODO: Impl load process for Texture1D 
	}

	void Texture::LoadTexture2D()
	{
		glGenTextures(1, &m_id);

		std::string filePath = GetFilePath();

		int width;
		int height;
		int nrComponents;
		unsigned char* data = stbi_load(filePath.c_str(), &width, &height, &nrComponents, 0);

		m_width = static_cast<uint32>(width);
		m_height = static_cast<uint32>(height);

		switch (nrComponents)
		{
		case 1:
			m_textureFormat = TextureFormat::TextureGrey;
			break;

		case 3:
			m_textureFormat = TextureFormat::TextureRGB;
			break;

		case 4:
			m_textureFormat = TextureFormat::TextureRGBA;
			break;
		}

		// @TODO: Metadata를 이용해서 조정 가능하도록.
		Bind();
		glTexImage2D(GL_TEXTURE_2D, 0,
			static_cast<GLuint>(m_textureFormat),
			width, height, 0,
			static_cast<GLuint>(m_textureFormat),
			GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		stbi_image_free(data);
	}

	void Texture::LoadTexture3D()
	{
		//@TODO: Impl load process for Texture3D
	}
}