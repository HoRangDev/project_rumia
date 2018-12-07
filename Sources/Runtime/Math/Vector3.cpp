#include "Math/Vector3.hpp"

namespace rumia
{
   Vector3::Vector3() :
      Vector3(0.0f, 0.0f, 0.0f)
   {
   }

   Vector3::Vector3(float _xyz) :
      Vector3(_xyz, _xyz, _xyz)
   {
   }

   Vector3::Vector3(float _xx, float _yy, float _zz) :
      xx(_xx),
      yy(_yy),
      zz(_zz)
   {
   }

   Vector3::Vector3(const Vector3& _vec3) :
      Vector3(_vec3.xx, _vec3.yy, _vec3.zz)
   {
   }

   const Vector3 Vector3::Right = Vector3{ 1.0f, 0.0f, 0.0f };
   const Vector3 Vector3::Up = Vector3{ 0.0f, 1.0f, 0.0f };
   const Vector3 Vector3::Forward = Vector3{ 0.0f, 0.0f, -1.0f };
   const Vector3 Vector3::Zero = Vector3{ 0.0f };
   const Vector3 Vector3::One = Vector3{ 1.0f };
}
