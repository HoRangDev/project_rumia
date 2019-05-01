#include "Component\Component.hpp"
#include "World\Actor.hpp"

namespace rumia
{
   Component::Component() :
      Component(nullptr)
   {
   }

   Component::Component(Actor* actor) :
      m_bActivated(true),
      m_actor(actor)
   {
	   Initialize();
   }

   Component::~Component()
   {
   }

   // Must call by derived Serialize
   json Component::Serialize() const
   {
      json object = json::object(); // Explicit empty object
      object["componentName"] = typeid(*this).name();
      object["activated"] = helper::BooleanToInt(m_bActivated);
      return object;
   }

   // Must call by derived DeSerialize
   void Component::DeSerialize(const json& object)
   {
      if (!object.is_null())
      {
         auto itr = object.find("activated");
         if (itr != object.end())
         {
            m_bActivated = helper::IntToBoolean(*itr);
         }
      }
   }

   bool Component::IsActivated() const
   {
      return (m_actor == nullptr) ? m_bActivated : (m_actor->IsActivated() && m_bActivated);
   }
}