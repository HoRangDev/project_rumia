#pragma once
#include "Core/EngineDefines.hpp"

namespace rumia
{
   class World;
   class Renderer;
   class ResourceManager;
   class RUMIA Engine
   {
   public:
      ~Engine();

      static Engine& GetInstance();

      bool Initialize(uint32 screenWidth, uint32 screenHeight, const std::string& title);

      void Tick();

      void Shutdown();

      ResourceManager& GetResourceManager() const { return (*m_resourceManager); }
      World& GetWorld() const { return (*m_world); }

   private:
      Engine();

   private:
      ResourceManager*  m_resourceManager;
      Renderer*         m_renderer;
      World*            m_world;

   private:
      static Engine* instance;

   };
}