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
      Vector2(const Vector2& _vec2);

   public:
      float xx;
      float yy;

   public:
      static const Vector2 Right;
      static const Vector2 Up;
      static const Vector2 Zero;
      static const Vector2 One;
   };
}