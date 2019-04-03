#pragma once
#include "Resource/Resource.hpp"
#include "Rendering/RenderingDefs.hpp"

namespace rumia
{
   //@TODO: Support tessellation stage
   enum class EShaderType : uint8
   {
      VertexShader,
      GeometryShader,
      FragmentShader,
      Unknown,
   };

   RUMIA static EShaderType FileExtensionToShaderType(const std::string& ext)
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

      return EShaderType::Unknown;
   }

   class RUMIA Shader : public Resource
   {
   public:
      Shader();
      ~Shader();

      virtual bool LoadProcess(std::ifstream& file) override;
      virtual void UnloadProcess() override;

      virtual void SaveProcess(std::ofstream& file) const override;

      GLuint GetID() const { return m_id; }
      EShaderType GetShaderType() const { return m_shaderType; }

   private:
      std::string m_shaderCode;
      EShaderType m_shaderType;
      GLuint      m_id;

   };
}
