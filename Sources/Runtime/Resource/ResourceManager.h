#pragma once
#include "Resource/Resource.hpp"

#include <unordered_map>

namespace rumia
{
   class RUMIA ResourceManager
   {
   public:
      ~ResourceManager()
      {
         Clear();
      }

      template <typename Ty>
      Ty* Load(const std::string& resPath)
      {
         Ty* res = nullptr;
         auto founded = m_resourceMap.find(resPath);
         if (founded != m_resourceMap.end())
         {
            res = static_cast<Ty*>((*founded).second);
         }
         else
         {
            res = new Ty();
            if (res->Load(resPath))
            {
               m_resourceMap[resPath] = res;
            }
            else
            {
               SafeDelete(res);
            }
         }

         if (res != nullptr)
         {
            res->IncRefCount();
         }

         return res;
      }

      bool Unload(Resource* res)
      {
         if (res != nullptr)
         {
            std::string resPath = res->GetFilePath();
            auto found = m_resourceMap.find(resPath);
            if (found != m_resourceMap.end())
            {
               Resource* foundRes = (*found).second;
               if (foundRes == res)
               {
                  res->DecRefCount();
                  if (res->GetRefCount() == 0)
                  {
                     SafeDelete(res);
                     m_resourceMap.erase(found);
                  }

                  return true;
               }
            }
         }

         return false;
      }

      void Clear()
      {
         for (auto resPair : m_resourceMap)
         {
            Resource* res = (resPair).second;
            SafeDelete(res);
         }

         m_resourceMap.clear();
      }

   private:
      ResourceManager() { }
      friend class Engine;

   private:
      std::unordered_map<std::string, Resource*>   m_resourceMap;

   };
}