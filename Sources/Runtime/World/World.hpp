#pragma once
#include "Core/EngineDefines.hpp"

#include <string>
#include <vector>

namespace rumia
{
   class Actor;
   class RUMIA World
   {
   public:
      ~World();

      void LoadFromFile(const std::string& filePath);

      Actor* CreateActor();
      void AddActor(Actor* actor);
      void RemoveActor(Actor* actor);

      void Unload();

      void Tick();

   private:
      World();

   private:
      std::vector<Actor*>  m_actors;
   };
}