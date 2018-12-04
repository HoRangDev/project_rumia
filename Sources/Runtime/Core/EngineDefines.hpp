#pragma once
#pragma warning(disable: 4251)
#pragma warning(disable: 4275)
#pragma warning(disable: 4099)

#define WIN32_MEAN_AND_LEAN

#ifdef RUNTIME_EXPORTS
#define RUMIA __declspec(dllexport)
#else
#define RUMIA __declspec(dllimport) 
#endif

namespace rumia
{
   template <typename Ty>
   void SafeDelete(Ty& target)
   {
      if (target != nullptr)
      {
         delete target;
         target = nullptr;
      }
   }

   template <typename Ty>
   void SafeRelease(Ty& target)
   {
      if (target != nullptr)
      {
         target->Release();
         target = nullptr;
      }
   }
}