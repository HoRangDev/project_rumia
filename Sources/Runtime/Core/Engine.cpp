#include "Core/Engine.hpp"
#include "Core/EventManager.hpp"
#include "Resource/ResourceManager.h"
#include "World/World.hpp"

namespace rumia
{
   Engine* Engine::instance = nullptr;
   Engine::Engine() :
      m_resourceManager(nullptr),
      m_renderer(nullptr),
      m_world(nullptr)
   {
   }

   Engine::~Engine()
   {
      Shutdown();
   }

   Engine& Engine::GetInstance()
   {
      if (instance == nullptr)
      {
         instance = new Engine();
      }

      return (*instance);
   }

   bool Engine::Initialize(uint32 screenWidth, uint32 screenHeight, const std::string& title)
   {
      //@TODO: Renderer, and init other systems
      if (m_world == nullptr)
      {
         m_world = new World();
         if (!m_world->Initialize())
         {
            return false;
         }
      }

      return true;
   }

   void Engine::Tick()
   {
      // @TODO: Need to measure elapsed time!!
      NOTIFY_WITH_DATA(EEngineEvent::Tick, 0.0f);
      NOTIFY(EEngineEvent::Render);
   }

   void Engine::Shutdown()
   {
      SafeDelete(m_world);
      SafeDelete(m_renderer);
      SafeDelete(m_resourceManager);
      // @TODO: Add loop flag
   }
}