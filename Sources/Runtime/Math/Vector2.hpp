#pragma once
#include "Core/EngineDefines.hpp"

namespace rumia
{
   struct RUMIA Vector2
   {
   public:
      Vector2();
      Vector2(float _xy);
      Vector2(float _xx, float _yy);

   public:
      float xx;
      float yy;
   };
}