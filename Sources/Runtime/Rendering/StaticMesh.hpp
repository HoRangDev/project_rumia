#pragma once
#include <glm/glm.hpp>
#include <vector>
#include "Core/EngineDefines.hpp"
#include "Rendering/RenderingDefs.hpp"

namespace rumia
{
   struct RUMIA VertexPTN
   {
      glm::vec3 Position;
      glm::vec2 TexCoord;
      glm::vec3 Normal;
   };

   class RUMIA StaticMesh
   {
   public:
      StaticMesh(const std::vector<VertexPTN>& vertices, const std::vector<uint32>& indices);

      void Draw(class Shader* shader);

   private:
      void Initialize();

   private:
      bool m_bInitialized;

      std::vector<VertexPTN>           m_vertices;
      std::vector<uint32>              m_indices;

      GLuint   m_vao;
      GLuint   m_vbo;
      GLuint   m_ebo;

   };
}