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

#define TYPE_TO_LITERAL(TYPE) #TYPE

namespace rumia
{
   /* x64 platform **/
   using SizeType = unsigned long long;

   /* Memory Management Utility functions **/
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