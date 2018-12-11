#pragma once
#include "Core/EngineDefines.hpp"
#include "Component/Component.hpp"

#include <string>
#include <vector>
#include <algorithm>

namespace rumia
{
   class Transform;
   class Renderable;
   class RUMIA Actor
   {
   public:
      Actor(const std::string& name = "Actor");
      virtual ~Actor();

      json Serialize() const;
      void DeSerialize(const json& object);

      template <typename Ty>
      Ty* AttachComponent()
      {
         if (Ty::GetTypeStatic() != EComponentType::Transform || m_transform == nullptr)
         {
            Ty* component = ComponentRegistry::GetInstance().Acquire<Ty>(this);
            if (component != nullptr)
            {
               m_components.emplace_back(component);

               // Caching renderable component
               if (component->GetType() == EComponentType::Renderable)
               {
                  m_renderable = reinterpret_cast<Renderable*>(component);
               }
            }

            return component;
         }

         return nullptr;
      }

      /* typeName = typeid(Ty).name() **/
      Component* AttachComponent(const std::string& typeName);

      template <typename Ty>
      Ty* GetComponent() const
      {
         for (uint64 idx = 0; idx < m_components.size(); ++idx)
         {
            if (typeid(*m_components[idx]) == typeid(Ty))
            {
               return static_cast<Ty*>(m_components[idx]);
            }
         }

         return nullptr;
      }

      template <typename Ty>
      std::vector<Ty*> GetComponents() const
      {
         std::vector<Ty*> components;
         for (Component* component : m_components)
         {
            if (typeid(*component) == typeid(Ty))
            {
               components.emplace_back(component);
            }
         }

         return std::move(m_components);
      }

      std::vector<Component*> GetComponentsAll() const { return m_components; }

      template <typename Ty>
      void DetachComponent()
      {
         if (typeid(Ty) != typeid(Transform))
         {
            auto foundItr = std::find_if(m_components.begin(), m_components.end(),
               [](Component* item)
            {
               return typeid(*item).name() == Ty::GetTypeName();
            });

            if (foundItr != m_components.end())
            {
               Component* found = *foundItr;
               if (found != nullptr)
               {
                  delete found;
                  found = nullptr;
               }

               m_components.erase(foundItr);
            }
         }
      }

      void Tick();

      Transform* GetTransform() const { return m_transform; }
      Renderable* GetRenderable() const { return m_renderable; }

      void SetName(const std::string& name) { m_name = name; }
      std::string GetName() const { return m_name; }
      uint64 GetID() const { return m_id; }

      bool HasParent() const;
      void SetActive(bool bActive) { m_bActivated = bActive; }
      bool IsLocalActivated() const { return m_bActivated; }
      bool IsActivated() const;

   protected:
      // After Actor constructor finished
      virtual void OnCreate() {}
      // Before Actor destructor called
      virtual void OnDestroy() {}

   private:
      bool           m_bActivated;
      std::string    m_name;
      uint64         m_id;
      std::vector<Component*> m_components;

      Transform*  m_transform;
      Renderable* m_renderable;

   private:
      static uint64 staticIDCount;
   };
}