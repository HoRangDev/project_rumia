#pragma once

#include "Resource/Resource.hpp"
#include "Rendering/RenderingDefs.hpp"

namespace rumia
{
	enum class TextureType
	{
		Texture1D,
		Texture2D,
		Texture3D,
		Cubemap,
	};

	enum TextureFormat
	{
		TextureGrey = GL_RED,
		TextureRGB = GL_RGB,
		TextureRGBA = GL_RGBA
	};

	class Texture : public Resource
	{
	public:
		Texture(const std::string& filePath);
		~Texture();

		uint32 GetWidth() const { m_width; }
		uint32 GetHeight() const { m_height; }
		uint32 GetDepth() const { m_depth; }
		
		TextureType GetTextureType() const { return m_textureType; }
		TextureFormat GetTextureFormat() const { return m_textureFormat; }
		
		virtual bool LoadProcess() override;
		virtual void UnloadProcess() override;

		void Bind();

	private:
		void LoadCubemap();
		void LoadTexture1D();
		void LoadTexture2D();
		void LoadTexture3D();

	private:
		TextureType		m_textureType;
		TextureFormat	m_textureFormat;
		uint32			m_width;
		uint32			m_height;
		uint32			m_depth;
		GLuint			m_id;

	};
}