#include "Core/Engine.hpp"
#include "Core/EventManager.hpp"
#include "World/World.hpp"

namespace rumia
{
   Engine* Engine::instance = nullptr;
   Engine::Engine() :
      m_world(nullptr),
      m_renderer(nullptr)
   {
   }

   Engine::~Engine()
   {
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
      // @TODO: Need to measure delta time!!
      NOTIFY_WITH_DATA(EEngineEvent::Tick, 0.0f);
      NOTIFY(EEngineEvent::Render);
   }

   void Engine::Shutdown()
   {
      //@TODO: Remove systems, set loop flags to false
   }

   //bool Engine::InitWindow(uint32 screenWidth, uint32 screenHeight, const std::string& title )
   //{
   //   glfwInit();
   //   glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
   //   glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
   //   glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

   //   m_window = glfwCreateWindow(screenWidth, screenHeight, title.c_str(), nullptr, nullptr);
   //   if (m_window == nullptr)
   //   {
   //      // @TODO: Error log failed to init window
   //      return false;
   //   }

   //   glfwMakeContextCurrent(m_window);
   //   // @TODO: Window callbacks like size callback, mouse, scroll, keyboard.. etc

   //   glfwSetInputMode(m_window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

   //   if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
   //   {
   //      // @TODO: Error log failed to init glad
   //      return false;
   //   }

   //   // Now its able to init opengl!
   //   return true;
   //}
}