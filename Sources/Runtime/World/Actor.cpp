#include "Actor.hpp"
#include "Component/Transform.hpp"

namespace rumia
{
   uint64 Actor::staticIDCount = 0;

   Actor::Actor(const std::string& name) :
      m_bActivated(true),
      m_name(name),
      m_id(staticIDCount),
      m_transform(nullptr),
      m_renderable(nullptr)
   {
      ++Actor::staticIDCount;

      // Actor always have own transform
      m_transform = AttachComponent<Transform>();

      OnCreate();
   }

   // Actor has responsability to delete components
   Actor::~Actor()
   {
      OnDestroy();
      for (uint64 idx = 0; idx < m_components.size(); ++idx)
      {
         delete m_components[idx];
      }

      m_components.clear();
   }

   json Actor::Serialize() const
   {
      json object = json::object();

      object["name"] = m_name;
      object["activated"] = helper::BooleanToInt(m_bActivated);

      json componentList = json::array();
      for (Component* component : m_components)
      {
         componentList += component->Serialize();
      }
      object["components"] = componentList;

      std::vector<Transform*> children = m_transform->GetChildren();
      json childList = json::array();
      for (Transform* child : children)
      {
         Actor* childActor = child->GetActor();
         childList += (childActor->Serialize());
      }
      object["children"] = childList;

      return object;
   }

   void Actor::DeSerialize(const json& object)
   {
      if (!object.is_null())
      {
         auto itr = object.find("name");
         if (itr != object.end())
         {
            m_name = (*itr).get<std::string>();
         }

         itr = object.find("activated");
         if (itr != object.end())
         {
            m_bActivated = helper::IntToBoolean(*itr);
         }

         // Component De-serialize
         itr = object.find("components");
         if (itr != object.end())
         {
            json componentList = (*itr);
            for (json component : componentList)
            {
               auto compItr = component.find("componentName");
               if (compItr != component.end())
               {
                  std::string componentName = (*compItr).get<std::string>();
                  if (componentName == typeid(Transform).name())
                  {
                     m_transform->DeSerialize(component);
                  }
                  else
                  {
                     Component* newComponent = AttachComponent(componentName);
                     newComponent->DeSerialize(component);
                  }
               }
            }
         }

         // Children Deserialize
         itr = object.find("children");
         if (itr != object.end())
         {
            json childList = (*itr);
            for (json childObject : childList)
            {
               Actor* newActor = new Actor();
               newActor->DeSerialize(childObject);
               newActor->GetTransform()->SetParent(m_transform);
            }
         }
      }
   }

   Component* Actor::AttachComponent(const std::string& typeName)
   {
      Component* component = ComponentRegistry::GetInstance().Acquire(typeName, this);
      if (component != nullptr)
      {
         if (component->GetType() == EComponentType::Transform)
         {
            SafeDelete(component);
         }
         else
         {
            m_components.emplace_back(component);

            if (component->GetType() == EComponentType::Renderable)
            {
               m_renderable = reinterpret_cast<Renderable*>(component);
            }
         }
      }

      return component;
   }

   void Actor::Tick()
   {
      for (Component* component : m_components)
      {
         component->Tick();
      }
   }

   bool Actor::HasParent() const
   {
      return (m_transform->GetParent() != nullptr);
   }

   bool Actor::IsActivated() const
   {
      Transform* parentTransform = m_transform->GetParent();
      return (parentTransform == nullptr) ? 
         (m_bActivated) : 
         (m_bActivated && parentTransform->GetActor()->IsActivated());
   }
}