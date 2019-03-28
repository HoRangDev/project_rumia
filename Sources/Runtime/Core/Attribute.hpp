#pragma once
#include "EngineDefines.hpp"

#include "glm/glm.hpp"

#include <variant>

namespace rumia
{
   enum class RUMIA EShaderAttributeType
   {
      Int32,
      Float,
      Double,
      Vec3,
      Vec4,
      Matrix4x4,
   };

   using ShaderAttribute = std::variant<
      int32, float, double,
      glm::vec3, glm::vec4, 
      glm::mat4x4>;

   RUMIA EShaderAttributeType GetTypeOfShaderAttribute(const ShaderAttribute& attrib)
   {
      return static_cast<EShaderAttributeType>(attrib.index());
   }

   RUMIA bool IsShaderAttrbuteType(const ShaderAttribute& attrib, EShaderAttributeType type)
   {
      return (GetTypeOfShaderAttribute(attrib) == type);
   }
}