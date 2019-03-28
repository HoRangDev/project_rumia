#include "Rendering/Mesh.hpp"

namespace rumia
{
   Mesh::Mesh(const std::string& meshName) :
      m_bInitialized(false),
      m_meshName(meshName),
      m_material(nullptr)
   {
   }

   Mesh::~Mesh()
   {
   }

   void Mesh::Initialize()
   {
      if (!m_bInitialized)
      {
         m_bInitialized = Initialize_Impl();
      }
   }

   void Mesh::Render(Renderer* renderer)
   {
      bool bIsMaterialAvailable = m_material != nullptr;
      if (m_bInitialized && bIsMaterialAvailable)
      {
         /*Render_Impl(renderer);*/
         //renderer->Enqueue(m_material, this);
      }
   }
}