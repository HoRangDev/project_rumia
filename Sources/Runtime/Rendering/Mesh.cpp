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
      if (bool bIsMaterialAvailable = m_material != nullptr; 
               m_bInitialized && bIsMaterialAvailable)
      {
         //renderer->Enqueue(m_material, this);
      }
   }
}