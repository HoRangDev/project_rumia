#include "Resource/Model.hpp"
#include "Rendering/Mesh.hpp"

namespace rumia
{
   void Model::Render(Renderer* renderer)
   {
      for (auto mesh : m_meshes)
      {
         mesh->Render(renderer);
      }
   }
}