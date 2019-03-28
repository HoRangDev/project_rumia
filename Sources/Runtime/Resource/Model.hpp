#pragma once
#include "Resource/Resource.hpp"

namespace rumia
{
   // Model meta data:
   // Model file/mesh type/preprocess flags/mesh-material table
   class Renderer;
   class Mesh;
   class RUMIA Model : public Resource 
   {
   public:
      Model(const std::string& filePath);
      ~Model();

      void Render(Renderer* renderer);

   private:
      std::vector<Mesh*>      m_meshes;

   };
}