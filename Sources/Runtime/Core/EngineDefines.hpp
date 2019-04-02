#pragma once
#pragma warning(disable: 4251)
#pragma warning(disable: 4275)
#pragma warning(disable: 4099)
#pragma warning(disable: 4996)

#define WIN32_MEAN_AND_LEAN

#ifdef RUNTIME_EXPORTS
#define RUMIA __declspec(dllexport)
#elif RUNTIME_EXPORTS_IGNORE
#define RUMIA 
#else
#define RUMIA __declspec(dllimport) 
#endif

#define TYPE_TO_LITERAL(TYPE) #TYPE

#include <string>
#include <string_view>
using namespace std::string_view_literals;

namespace rumia
{
   constexpr auto MetafileExtension = ".meta"sv;
   constexpr auto FileDirectorySeparator = "/";

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

   /* Types **/
   using uint8 = unsigned char;
   using int8 = signed char;
   using uint16 = unsigned short;
   using int16 = signed short;
   using uint32 = unsigned int;
   using int32 = signed int;
   using uint64 = unsigned long long;
   using int64 = long long;
}