#pragma once
#include "Component/Component.h"

namespace rumia
{
   class TestComponent : public Component
   {
      RUMIA_COMPONENT(TestComponent);

   protected:
      TestComponent(Actor* actor) :
         Component(actor)
      {
      }
   };
}