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
}