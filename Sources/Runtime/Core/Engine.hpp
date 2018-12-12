#pragma once
#include "Core/EngineDefines.hpp"

#include <string>

namespace rumia
{
   class RUMIA Engine
   {
   public:
      ~Engine();

      static Engine& GetInstance();

      bool Initialize(uint32 screenWidth, uint32 screenHeight, const std::string& title);

      void Tick();

      void Shutdown();

   private:
      Engine();

   private:
      static Engine* instance;

   };
}