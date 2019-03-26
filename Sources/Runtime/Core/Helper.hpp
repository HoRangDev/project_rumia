#pragma once
#include "EngineDefines.hpp"

#include "json.hpp"
#include "glm/glm.hpp"
#include "glm/gtc/quaternion.hpp"
#include "glm/gtx/quaternion.hpp"
#include "glm/gtc/type_ptr.hpp"

using namespace nlohmann;

namespace rumia
{
   namespace helper
   {
	   /* Serializer */
      RUMIA json SerializeVec2(const glm::vec2& vec);
      RUMIA json SerializeVec3(const glm::vec3& vec);
      RUMIA json SerializeVec4(const glm::vec4& vec);
      RUMIA json SerializeQuaternion(const glm::quat& quat);

      RUMIA glm::vec2 DeSerializeVec2(const json& object);
      RUMIA glm::vec3 DeSerializeVec3(const json& object);
      RUMIA glm::vec4 DeSerializeVec4(const json& object);
      RUMIA glm::quat DeSerializeQuaternion(const json& object);

      RUMIA uint32 BooleanToInt(bool bState);
      RUMIA bool IntToBoolean(uint32 state);

      template <typename Ty>
      json Serialize(const Ty& serializable)
      {
         return serializable->Serialize();
      }

      template <typename Ty>
      void DeSerialize(Ty& serializable, const json& object)
      {
         serializable->DeSerialize(object);
      }

      template <typename Ty>
      void DeSerialize(Ty& serializable, const std::string& serializedStr)
      {
         serializable->DeSerialize(json::parse(serializedStr));
      }
	  /************************************************************************/

	  /* String */
	  RUMIA std::vector<std::string> SplitString(const std::string& str, char token);
	  RUMIA std::vector<std::string> SplitString(const std::string& str, const std::vector<char>& tokens);
	  /************************************************************************/

   }
}