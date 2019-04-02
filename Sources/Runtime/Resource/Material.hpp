#pragma once
#include "Resource/Shader.hpp"
#include "Core/Attribute.hpp"

#include <unordered_map>

namespace rumia
{
   // Material meta-data: shader ref/shader parameters
   class Shader;
   class Texture;
   class RUMIA Material : public Resource
   {
   public:
      Material();
      ~Material();

      void Bind();

      bool IsValid() const;

      void SetAttribute(const std::string& name, const ShaderAttribute& attribute);

      void SetVertexShader(Shader* shader);
      void SetGeometryShader(Shader* shader);
      void SetFragmentShader(Shader* shader);

      virtual bool LoadProcess(std::ifstream& file) override;
      virtual void UnloadProcess() override;

      virtual void SaveProcess(std::ofstream& file) const override;

   private:
      void BindShaders();
      void BindAttributes();

      void SetInt(const std::string& key, int32 val);
      void SetFloat(const std::string& key, float val);
      void SetVec3f(const std::string& key, const glm::vec3& val);
      void SetVec4f(const std::string& key, const glm::vec4& val);
      void SetMat4x4f(const std::string& key, const glm::mat4x4& val);

   private:
      // Shaders
      GLuint  m_program;
      Shader* m_vertexShader;
      Shader* m_geometryShader;
      Shader* m_fragmentShader;

      bool  m_bFirstBind;
      bool  m_bDirty;

      std::unordered_map<std::string, ShaderAttribute>   m_attributes;

   };
}
