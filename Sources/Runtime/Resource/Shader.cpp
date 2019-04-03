#include "Resource/Shader.hpp"

namespace rumia
{
   Shader::Shader() :
      m_shaderType(EShaderType::Unknown),
      m_id(0),
      Resource(EResourceType::Shader)
   {
   }

   Shader::~Shader()
   {
   }

   bool Shader::LoadProcess(std::ifstream& file)
   {
      std::stringstream shaderStream;
      shaderStream << file.rdbuf();

      m_shaderCode = shaderStream.str();

      std::string fileExt = GetFileExt();
      EShaderType shaderType = FileExtensionToShaderType(fileExt);
      switch (shaderType)
      {
      case EShaderType::VertexShader:
         m_id = glCreateShader(GL_VERTEX_SHADER);
         break;

      case EShaderType::GeometryShader:
         m_id = glCreateShader(GL_GEOMETRY_SHADER);
         break;

      case EShaderType::FragmentShader:
         m_id = glCreateShader(GL_FRAGMENT_SHADER);
         break;

      default:
         return false;
      }

      const char* source = m_shaderCode.data();
      glShaderSource(m_id, 1, &source, nullptr);
      glCompileShader(m_id);

      // @TODO: Check compile error
      return true;
   }

   void Shader::UnloadProcess()
   {
      glDeleteProgram(m_id);
      m_id = 0;
      m_shaderCode.clear();
      m_shaderCode.shrink_to_fit();
   }

   void Shader::SaveProcess(std::ofstream& file) const
   {
      file << m_shaderCode;
   }
}