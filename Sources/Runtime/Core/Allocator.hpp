#pragma once
#include "Core/EngineDefines.hpp"

namespace rumia
{
   class RUMIA Allocator
   {
   public:
      virtual void* Allocate(SizeType sizeOfChunk) = 0;
      virtual void Deallocate(void* targetMemPtr) = 0;
   };
}