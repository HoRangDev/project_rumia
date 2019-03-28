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
		Texture(const std::string& filePath);
		~Texture();

		uint32 GetWidth() const { return m_width; }
		uint32 GetHeight() const { return m_height; }
		uint32 GetDepth() const { return m_depth; }
		
		ETextureType GetTextureType() const { return m_textureType; }
		ETextureFormat GetTextureFormat() const { return m_textureFormat; }

        GLuint GetID() const { return m_id; }
		
		virtual bool LoadProcess() override;
		virtual void UnloadProcess() override;

		void Bind();

	private:
		void LoadCubemap();
		void LoadTexture1D();
		void LoadTexture2D();
		void LoadTexture3D();

	private:
		ETextureType	m_textureType;
		ETextureFormat	m_textureFormat;
		uint32			m_width;
		uint32			m_height;
		uint32			m_depth;
		GLuint			m_id;

	};
}