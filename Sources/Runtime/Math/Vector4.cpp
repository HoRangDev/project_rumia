#include "Math/Vector4.hpp"
#include "Math/Vector3.hpp"

namespace rumia
{
   Vector4::Vector4() :
      Vector4(0.0f, 0.0f, 0.0f, 0.0f)
   {
   }

   Vector4::Vector4(float _xyzw) :
      Vector4(_xyzw, _xyzw, _xyzw, _xyzw)
   {
   }

   Vector4::Vector4(const Vector3& _vec3) :
      Vector4(_vec3, 0.0f)
   {
   }

   Vector4::Vector4(const Vector3& _vec3, float _ww) :
      Vector4(_vec3.xx, _vec3.yy, _vec3.zz, _ww)
   {
   }

   Vector4::Vector4(float _xx, float _yy, float _zz) :
      Vector4(_xx, _yy, _zz, 0.0f)
   {
   }

   Vector4::Vector4(float _xx, float _yy, float _zz, float _ww) :
      xx(_xx),
      yy(_yy),
      zz(_zz),
      ww(_ww)
   {
   }

   const Vector4 Vector4::Right = Vector4{1.0f, 0.0f, 0.0f, 0.0f};
   const Vector4 Vector4::Up = Vector4{0.0f, 1.0f, 0.0f, 0.0f};
   const Vector4 Vector4::Forward = Vector4{0.0f, 0.0f, 0.0f, 0.0f};
   const Vector4 Vector4::Zero = Vector4{0.0f};
   const Vector4 Vector4::One = Vector4{1.0f};
}
