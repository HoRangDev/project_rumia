#pragma once
#include "Resource/Resource.hpp"
#include "Rendering/RenderingDefs.hpp"

namespace rumia
{
   //@TODO: Support tessellation stage
   enum class EShaderType
   {
      VertexShader,
      GeometryShader,
      FragmentShader,
      Unknwon
   };

   EShaderType FileExtensionToShaderType(const std::string& ext)
   {
      if (ext == ".vs")
      {
         return EShaderType::VertexShader;
      }
      else if (ext == ".gs")
      {
         return EShaderType::GeometryShader;
      }
      else if (ext == ".fs")
      {
         return EShaderType::FragmentShader;
      }

      return EShaderType::Unknwon;
   }

   class RUMIA Shader : public Resource
   {
   public:
      Shader(const std::string& filePath);
      ~Shader();

      virtual bool LoadProcess() override;
      virtual void UnloadProcess() override;

      GLuint GetID() const { return m_id; }
      EShaderType GetShaderType() const { return m_shaderType; }

   private:
      EShaderType m_shaderType;
      GLuint      m_id;

   };
}
