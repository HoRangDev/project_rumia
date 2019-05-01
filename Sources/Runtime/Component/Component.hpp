#pragma once
#include "Core/Helper.hpp"

#include <string>
#include <map>
#include <functional>
#include <type_traits>

namespace rumia
{
   enum class RUMIA EComponentType
   {
      None,
      Transform,
      Renderable,
      Light,
      Script
   };

   class Actor;
   class RUMIA Component
   {
   public:
      virtual ~Component();

      Actor* GetActor() const { return m_actor; }

      virtual void Tick() {}

      virtual json Serialize() const;
      virtual void DeSerialize(const json& object);

      virtual EComponentType GetType() const = 0;

      void SetActive(bool bActive) { m_bActivated = bActive; }
      bool IsActivated() const;

	  virtual void Initialize() { /* Empty Function! */ }
	  virtual void DeInitialize() { /* Empty Function! */ }

   protected:
      Component();
      Component(Actor* actor);

   private:
      bool        m_bActivated;
      Actor*      m_actor;

   private:
      static uint64 componentCount;

   };

   class RUMIA ComponentRegistry
   {
      friend class Actor;
   private:
      ComponentRegistry()
      {
         // @Empty
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

   private: 
      std::map< std::string, std::function<Component*(Actor*)> > componentMap;
   };
}

#define RUMIA_ABSTRACT_COMPONENT(TYPE) protected: TYPE() { /* Empty function */}

#define RUMIA_COMPONENT(TYPE, ComponentType) public: virtual EComponentType GetType() const override { return ComponentType; }\
                              static EComponentType GetTypeStatic() { return ComponentType; } \
                              private: friend class rumia::ComponentRegistry; static TYPE _registerInst; \
                              static TYPE* Create(Actor* actor) { return new TYPE(actor);} \
                              protected: TYPE() { rumia::ComponentRegistry::GetInstance().Register<TYPE>(); } \

#define RUMIA_REGISTER_COMPONENT(TYPE) TYPE TYPE::_registerInst;
