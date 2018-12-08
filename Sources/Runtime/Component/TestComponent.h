#pragma once
#include "Component/Component.hpp"

namespace rumia
{
   class TestComponent : public Component
   {
      RUMIA_COMPONENT(TestComponent, EComponentType::Script);

   protected:
      TestComponent(Actor* actor) :
         Component(actor)
      {
      }
   };
}