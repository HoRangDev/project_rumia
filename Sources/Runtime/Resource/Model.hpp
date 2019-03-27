#pragma once
#include "Resource/Resource.hpp"

namespace rumia
{
   class RUMIA Model : public Resource 
   {
   public:
      Model(const std::string& filePath);
      ~Model();

   private:
      std::vector<class Mesh*>      m_meshes;
      std::vector<class Texture*>   m_textures;

   };
}