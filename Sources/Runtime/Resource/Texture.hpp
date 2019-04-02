#pragma once

#include "Resource/Resource.hpp"
#include "Rendering/RenderingDefs.hpp"

namespace rumia
{
	enum class RUMIA ETextureType
	{
		Texture1D,
		Texture2D,
		Texture3D,
		Cubemap,
	};

	enum RUMIA ETextureFormat
	{
		TextureGrey = GL_RED,
		TextureRGB = GL_RGB,
		TextureRGBA = GL_RGBA
	};

	class RUMIA Texture : public Resource
	{
	public:
		Texture();
		~Texture();

		uint32 GetWidth() const { return m_width; }
		uint32 GetHeight() const { return m_height; }
		uint32 GetDepth() const { return m_depth; }
		
		ETextureType GetTextureType() const { return m_textureType; }
		ETextureFormat GetTextureFormat() const { return m_textureFormat; }

        GLuint GetID() const { return m_id; }
		
		virtual bool LoadProcess(std::ifstream& file) override;
		virtual void UnloadProcess() override;

		void Bind();

	private:
       unsigned char* LoadRawDataFromStream(std::ifstream& file, int& width, int& height, int& nrComponents); // Must be free with stbi_image_free
		bool LoadCubemap(std::ifstream& file);
		bool LoadTexture1D(std::ifstream& file);
		bool LoadTexture2D(std::ifstream& file);
		bool LoadTexture3D(std::ifstream& file);

	private:
		ETextureType	m_textureType;
		ETextureFormat	m_textureFormat;
		uint32			m_width;
		uint32			m_height;
		uint32			m_depth;
		GLuint			m_id;

	};
}