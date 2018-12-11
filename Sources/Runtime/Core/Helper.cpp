#include "Helper.hpp"

namespace rumia
{
   namespace helper
   {
      json SerializeVec2(const glm::vec2& vec)
      {
         json object;
         object["x"] = vec.x;
         object["y"] = vec.y;
         return object;
      }

      json SerializeVec3(const glm::vec3& vec)
      {
         json object;
         object["x"] = vec.x;
         object["y"] = vec.y;
         object["z"] = vec.z;
         return object;
      }

      json SerializeVec4(const glm::vec4& vec)
      {
         json object;
         object["x"] = vec.x;
         object["y"] = vec.y;
         object["z"] = vec.z;
         object["w"] = vec.w;
         return object;
      }

      json SerializeQuaternion(const glm::quat& quat)
      {
         json object;
         object["w"] = quat.w;
         object["x"] = quat.x;
         object["y"] = quat.y;
         object["z"] = quat.z;
         return object;
      }

      glm::vec2 DeSerializeVec2(const json& object)
      {
         glm::vec2 output;
         if (!object.is_null())
         {
            auto x = object.find("x");
            if (x->is_number())
            {
               output.x = (*x);
            }

            auto y = object.find("y");
            if (y->is_number())
            {
               output.y = (*y);
            }
         }

         return output;
      }

      glm::vec3 DeSerializeVec3(const json& object)
      {
         glm::vec3 output;

         if (!object.is_null())
         {
            auto x = object.find("x");
            if (x->is_number())
            {
               output.x = (*x);
            }

            auto y = object.find("y");
            if (y->is_number())
            {
               output.y = (*y);
            }

            auto z = object.find("z");
            if (z->is_number())
            {
               output.z = (*z);
            }
         }

         return output;
      }

      glm::vec4 DeSerializeVec4(const json& object)
      {
         glm::vec4 output;
         if (!object.is_null())
         {
            glm::vec3 xyzOutput = DeSerializeVec3(object);
            auto x = object.find("x");
            if (x->is_number())
            {
               output.x = (*x);
            }

            auto y = object.find("y");
            if (y->is_number())
            {
               output.y = (*y);
            }

            auto z = object.find("z");
            if (z->is_number())
            {
               output.z = (*z);
            }

            auto w = object.find("w");
            if (w->is_number())
            {
               output.w = (*w);
            }
         }

         return output;
      }

      glm::quat DeSerializeQuaternion(const json& object)
      {
         glm::quat output;

         auto w = object.find("w");
         if (w->is_number())
         {
            output.w = (*w);
         }
         auto x = object.find("x");
         if (x->is_number())
         {
            output.x = (*x);
         }
         auto y = object.find("y");
         if (y->is_number())
         {
            output.y = (*y);
         }
         auto z = object.find("z");
         if (z->is_number())
         {
            output.z = (*z);
         }

         return output;
      }

      uint32 BooleanToInt(bool bState)
      {
         return bState ? 1 : 0;
      }

      bool IntToBoolean(uint32 state)
      {
         return (state == 0) ? false : true;
      }
   }
}