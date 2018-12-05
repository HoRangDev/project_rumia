#include "Math/Vector2.hpp"

namespace rumia
{
   Vector2::Vector2() :
      Vector2(0.0f)
   {
   }

   Vector2::Vector2(float _xy) :
      Vector2(_xy, _xy)
   {
   }

   Vector2::Vector2(float _xx, float _yy) :
      xx(_xx),
      yy(_yy)
   {
   }

   Vector2::Vector2(const Vector2& _vec2) :
      Vector2(_vec2.xx, _vec2.yy)
   {
   }

   const Vector2 Vector2::Right = Vector2{ 1.0f, 0.0f };
   const Vector2 Vector2::Up = Vector2{ 0.0f, 1.0f };
   const Vector2 Vector2::Zero = Vector2{ 0.0f };
   const Vector2 Vector2::One = Vector2{ 1.0f };
}