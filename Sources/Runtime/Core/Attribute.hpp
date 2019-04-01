#pragma once
#include "EngineDefines.hpp"

#include "glm/glm.hpp"

#include <variant>

namespace rumia
{
   enum class RUMIA EShaderAttributeType
   {
      Texture,
      Int32,
      Float,
      Vec3,
      Vec4,
      Matrix4x4,
   };

   using ShaderAttribute = std::variant<
      class Texture*,
      int32, float,
      glm::vec3, glm::vec4,
      glm::mat4x4>;

   RUMIA static EShaderAttributeType GetTypeOfShaderAttribute(const ShaderAttribute& attrib)
   {
      return static_cast<EShaderAttributeType>(attrib.index());
   }

   RUMIA static bool IsShaderAttrbuteType(const ShaderAttribute& attrib, EShaderAttributeType type)
   {
      return (GetTypeOfShaderAttribute(attrib) == type);
   }
}