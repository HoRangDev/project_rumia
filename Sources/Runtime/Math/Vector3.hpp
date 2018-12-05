#pragma once
#include "Core/EngineDefines.hpp"

namespace rumia
{
   /*
   * @brief 3D Vector struct
   **/
   struct RUMIA Vector3
   {
   public:
      Vector3();
      Vector3(float _xyz);
      Vector3(float _xx, float _yy, float _zz);
      Vector3(const Vector3& _vec3);

   public:
      float xx;
      float yy;
      float zz;

   public:
      static const Vector3 Right;
      static const Vector3 Up;
      /* Left-Hand coordinate forward **/
      static const Vector3 Forward;
      static const Vector3 Zero;
      static const Vector3 One;
   };
}