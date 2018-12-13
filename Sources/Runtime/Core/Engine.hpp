#pragma once
#include "Core/EngineDefines.hpp"

#include <string>

namespace rumia
{
   class World;
   class Renderer;
   class RUMIA Engine
   {
   public:
      ~Engine();

      static Engine& GetInstance();

      bool Initialize(uint32 screenWidth, uint32 screenHeight, const std::string& title);

      void Tick();

      void Shutdown();

      World& GetWorld() const { return (*m_world); }

   private:
      Engine();

   private:
      World* m_world;
      Renderer* m_renderer;

   private:
      static Engine* instance;

   };
}