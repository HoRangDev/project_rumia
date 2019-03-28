#pragma once
#include <glm/glm.hpp>
#include <vector>
#include "Core/EngineDefines.hpp"
#include "Rendering/RenderingDefs.hpp"

namespace rumia
{
   class RUMIA Mesh
   {
   public:
      virtual ~Mesh() {}

      virtual void Draw(class Shader* shader) = 0;

   };
}