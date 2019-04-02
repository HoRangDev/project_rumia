#include "Resource/Material.hpp"
#include "Resource/Texture.hpp"

#include <array>

namespace rumia
{
   Material::Material() :
      m_program(0),
      m_vertexShader(nullptr),
      m_geometryShader(nullptr),
      m_fragmentShader(nullptr),
      m_bFirstBind(true),
      m_bDirty(true),
      Resource(EResourceType::Material)
   {
   }

   Material::~Material()
   {
      m_vertexShader = nullptr;
      m_geometryShader = nullptr;
      m_fragmentShader = nullptr;
   }

   void Material::Bind()
   {
      if (IsValid())
      {
         BindShaders();
         BindAttributes();
      }
   }

   bool Material::IsValid() const
   {
      return IsLoaded() && (m_vertexShader != nullptr) &&
         (m_fragmentShader != nullptr);
   }

   void Material::SetAttribute(const std::string& name, const ShaderAttribute& attribute)
   {
      auto found = m_attributes.find(name);
      if (found == m_attributes.end())
      {
         m_attributes[name] = attribute;
      }
   }

   void Material::SetVertexShader(Shader* shader)
   {
      if (m_vertexShader != shader)
      {
         m_vertexShader = shader;
         m_bDirty = true;
      }
   }

   void Material::SetGeometryShader(Shader* shader)
   {
      if (m_geometryShader != shader)
      {
         m_geometryShader = shader;
         m_bDirty = true;
      }
   }

   void Material::SetFragmentShader(Shader* shader)
   {
      if (m_fragmentShader != shader)
      {
         m_fragmentShader = shader;
         m_bDirty = true;
      }
   }

   void Material::BindShaders()
   {
      if (m_bDirty)
      {
         if (!m_bFirstBind)
         {
            glDeleteProgram(m_program);
         }

         m_program = glCreateProgram();
         if (m_vertexShader != nullptr &&
            m_vertexShader->IsLoaded())
         {
            glAttachShader(m_program, m_vertexShader->GetID());
         }
         if (m_geometryShader != nullptr &&
            m_geometryShader->IsLoaded())
         {
            glAttachShader(m_program, m_geometryShader->GetID());
         }
         if (m_fragmentShader != nullptr &&
            m_fragmentShader->IsLoaded())
         {
            glAttachShader(m_program, m_fragmentShader->GetID());
         }

         glLinkProgram(m_program);
         m_bFirstBind = false;
      }

      glUseProgram(m_program);
   }

   void Material::BindAttributes()
   {
      for (auto attributePair : m_attributes)
      {
         std::string attributeKey = attributePair.first;
         ShaderAttribute attribute = attributePair.second;

         EShaderAttributeType attributeType = GetTypeOfShaderAttribute(attribute);
         int32 textureCount = 0;
         switch (attributeType)
         {
         case rumia::EShaderAttributeType::Texture:
            glActiveTexture(textureCount + GL_TEXTURE0);
            std::get<Texture*>(attribute)->Bind();
            SetInt(attributeKey, textureCount);
            ++textureCount;
            break;
         case rumia::EShaderAttributeType::Int32:
            SetInt(attributeKey, std::get<int32>(attribute));
            break;
         case rumia::EShaderAttributeType::Float:
            SetFloat(attributeKey, std::get<float>(attribute));
            break;
         case rumia::EShaderAttributeType::Vec3:
            SetVec3f(attributeKey, std::get<glm::vec3>(attribute));
            break;
         case rumia::EShaderAttributeType::Vec4:
            SetVec4f(attributeKey, std::get<glm::vec4>(attribute));
            break;
         case rumia::EShaderAttributeType::Matrix4x4:
            SetMat4x4f(attributeKey, std::get<glm::mat4x4>(attribute));
            break;
         default:
            break;
         }
      }
   }

   void Material::SetInt(const std::string& key, int32 val)
   {
      glUniform1i(glGetUniformLocation(m_program, key.c_str()), val);
   }

   void Material::SetFloat(const std::string& key, float val)
   {
      glUniform1f(glGetUniformLocation(m_program, key.c_str()), val);
   }

   void Material::SetVec3f(const std::string& key, const glm::vec3& val)
   {
      glUniform3f(glGetUniformLocation(m_program, key.c_str()), val[0], val[1], val[2]);
   }

   void Material::SetVec4f(const std::string& key, const glm::vec4& val)
   {
      glUniform4f(glGetUniformLocation(m_program, key.c_str()), val[0], val[1], val[2], val[3]);
   }

   void Material::SetMat4x4f(const std::string& key, const glm::mat4x4& val)
   {
      glUniformMatrix4fv(glGetUniformLocation(m_program, key.c_str()),
         1, GL_FALSE,
         &val[0][0]);
   }
}