#include "Resource/Shader.hpp"

namespace rumia
{
   Shader::Shader(const std::string& filePath) :
      m_shaderType(EShaderType::Unknwon),
      m_id(0),
      Resource(filePath, EResourceType::Shader)
   {
   }

   Shader::~Shader()
   {
   }

   bool Shader::LoadProcess()
   {
      std::string_view filePath = GetFilePath();
      std::ifstream shaderFile;

      std::string shaderCode;

      shaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
      try
      {
         shaderFile.open(filePath.data());
         std::stringstream shaderStream;
         shaderStream << shaderFile.rdbuf();
         shaderFile.close();

         shaderCode = shaderStream.str();

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

         const char* source = shaderCode.data();
         glShaderSource(m_id, 1, &source, nullptr);
         glCompileShader(m_id);
         
         // @TODO: Check compile error
      }
      catch (std::ifstream::failure e)
      {
         //@TODO: Logging error message
         return false;
      }

      return true;
   }

   void Shader::UnloadProcess()
   {
   }
}