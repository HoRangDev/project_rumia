#pragma once
#include "Rendering/Mesh.h"

namespace rumia
{
   struct RUMIA VertexPTN
   {
      glm::vec3 Position;
      glm::vec2 TexCoord;
      glm::vec3 Normal;
   };

   class RUMIA StaticMesh : public Mesh
   {
   public:
      StaticMesh(const std::vector<VertexPTN>& vertices, const std::vector<uint32>& indices);

      virtual void Draw(class Shader* shader) override;

      GLuint GetVAO() const { return m_vao; }
      GLuint GetVBO() const { return m_vbo; }
      GLuint GetEBO() const { return m_ebo; }

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