#pragma once
#include "Core/EngineDefines.hpp"

#include <string>
#include <map>
#include <functional>
#include <type_traits>

namespace rumia
{
   class Actor;
   class RUMIA Component
   {
   protected:
      Component();
      Component(Actor* actor);
      virtual ~Component();

      Actor* GetActor() const { return m_actor; }

   private:
      Actor*      m_actor;

   private:
      static SizeType componentCount;

   };

   class RUMIA ComponentRegistry
   {
   private:
      ComponentRegistry()
      {
         // @Empty
      }

   public:
      static ComponentRegistry& GetInstance()
      {
         static ComponentRegistry registry;
         return registry;
      }

      template <typename Ty>
      void Register()
      {
         static_assert(std::is_base_of<Component, Ty>::value, " Ty is not a component!");
         std::string compType = typeid(Ty).name();
         auto itr = componentMap.find(compType);
         if (itr == componentMap.end())
         {
            componentMap.insert(std::make_pair(compType, &Ty::Create));
         }
      }

      template <typename Ty>
      Ty* Acquire(Actor* actor)
      {
         static_assert(std::is_base_of<Component, Ty>::value, " Ty is not a component!");
         return static_cast<Ty*>(Acquire(typeid(Ty).name(), actor));
      }

      Component* Acquire(const std::string& typeName, Actor* actor)
      {
         if (actor != nullptr)
         {
            std::string compType = typeName;
            auto itr = componentMap.find(compType);
            if (itr != componentMap.end())
            {
               return (*itr).second(actor);
            }
         }

         return nullptr;
      }

   private: 
      std::map< std::string, std::function<Component*(Actor*)> > componentMap;
   };
}

#define RUMIA_COMPONENT(TYPE) private: friend class rumia::ComponentRegistry; static TYPE _registerInst; \
                              static TYPE* Create(Actor* actor) { return new TYPE(actor);} \
                              TYPE() { rumia::ComponentRegistry::GetInstance().Register<TYPE>(); } \

#define RUMIA_REGISTER_COMPONENT(TYPE) TYPE TYPE::_registerInst;
