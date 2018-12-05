#pragma once
#include "Core/EngineDefines.hpp"

namespace rumia
{
   struct Vector3;
   struct RUMIA Vector4
   {
   public:
      Vector4();
      Vector4(float _xyzw);
      Vector4(float _xx, float _yy, float _zz);
      Vector4(const Vector3& _vec3);
      Vector4(const Vector3& _vec3, float _ww);
      Vector4(float _xx, float _yy, float _zz, float _ww);

   public:
      float xx;
      float yy;
      float zz;
      float ww;

   public:
      static const Vector4 Right;
      static const Vector4 Up;
      /* Left-Hand coordinate forward **/
      static const Vector4 Forward;
      static const Vector4 Zero;
      static const Vector4 One;
   };
}