#include "Component\Component.hpp"

namespace rumia
{
   Component::Component() :
      Component(nullptr)
   {
   }

   Component::Component(Actor* actor) :
      m_actor(actor)
   {
   }

   Component::~Component()
   {
   }

   json Component::Serialize() const
   {
      json object = json::object(); // Explicit empty object
      object["componentName"] = typeid(*this).name();
      return object;
   }

   void Component::DeSerialize(const json& object)
   {
      // #Empty
   }
}