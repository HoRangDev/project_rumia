#define STB_IMAGE_IMPLEMENTATION
#include "Resource/Texture.hpp"
#include "stb_image.h"

namespace rumia
{
	Texture::Texture() :
		m_width(0), m_height(0), m_depth(0),
		m_textureType(ETextureType::Texture2D),
		Resource(EResourceType::Texture)
	{
	}

	Texture::~Texture()
	{
	}

	bool Texture::LoadProcess(std::ifstream& file)
	{
		switch (m_textureType)
		{
		case ETextureType::Cubemap:
			return LoadCubemap(file);
		case ETextureType::Texture1D:
			return LoadTexture1D(file);
		case ETextureType::Texture2D:
			return LoadTexture2D(file);
		case ETextureType::Texture3D:
			return LoadTexture3D(file);
		}

        return false;
	}

	void Texture::UnloadProcess()
	{
		/* Nothing to do **/
	}

	void Texture::Bind()
	{
		switch (m_textureType)
		{
		case ETextureType::Cubemap:
			glBindTexture(GL_TEXTURE_CUBE_MAP, m_id);
		case ETextureType::Texture1D:
			glBindTexture(GL_TEXTURE_1D, m_id);
			break;
		case ETextureType::Texture2D:
			glBindTexture(GL_TEXTURE_2D, m_id);
			break;
		case ETextureType::Texture3D:
			glBindTexture(GL_TEXTURE_3D, m_id);
			break;
		}
	}

    unsigned char* Texture::LoadRawDataFromStream(std::ifstream& file, int& width, int& height, int& nrComponents)
    {
       std::vector<unsigned char> buffer;

       std::streampos begin = file.tellg();
       file.seekg(0, std::ios_base::end);
       std::streampos end = file.tellg();
       file.seekg(0, std::ios_base::beg);

       size_t bufferSize = (end - begin);

       buffer.reserve(bufferSize);
       buffer.assign(std::istreambuf_iterator<char>(file),
          std::istreambuf_iterator<char>());

       return stbi_load_from_memory(buffer.data(), (int)bufferSize, 
          &width, &height, 
          &nrComponents, 0);
    }

	bool Texture::LoadCubemap(std::ifstream& file)
	{
		//@TODO: Impl load process for Cubemap
       return false;
	}

	bool Texture::LoadTexture1D(std::ifstream& file)
	{
		//@TODO: Impl load process for Texture1D 
       return false;
	}

	bool Texture::LoadTexture2D(std::ifstream& file)
	{
		glGenTextures(1, &m_id);

		std::string filePath = GetFilePath();

		int width;
		int height;
		int nrComponents;
		//unsigned char* data = stbi_load(filePath.c_str(), &width, &height, &nrComponents, 0);
        unsigned char* data = LoadRawDataFromStream(file, width, height, nrComponents);

        if (data != nullptr)
        {
           m_width = static_cast<uint32>(width);
           m_height = static_cast<uint32>(height);

           switch (nrComponents)
           {
           case 1:
              m_textureFormat = ETextureFormat::TextureGrey;
              break;

           case 3:
              m_textureFormat = ETextureFormat::TextureRGB;
              break;

           case 4:
              m_textureFormat = ETextureFormat::TextureRGBA;
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

        return true;
	}

	bool Texture::LoadTexture3D(std::ifstream& file)
	{
		//@TODO: Impl load process for Texture3D
       return false;
	}
}