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
}