#pragma once
#include "Core/Helper.hpp"

#include <string>
#include <vector>

namespace rumia
{
   class Actor;
   class RUMIA World
   {
   public:
      World();
      ~World();

      bool Initialize();

      json Serialize() const;
      void DeSerialize(const json& object);

      void LoadFromFile(const std::string& filePath);
      void SaveToFile(const std::string& filePath);

      Actor* CreateActor();
      void AddActor(Actor* actor);
      void RemoveActor(Actor* actor);

      void Unload();

      void Tick();

   private:
      std::vector<Actor*>  m_actors;
   };
}