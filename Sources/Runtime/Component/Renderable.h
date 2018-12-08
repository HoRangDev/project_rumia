#pragma once
#include "Component/Component.hpp"

namespace rumia
{
   class RUMIA Renderable : public Component
   {
      RUMIA_COMPONENT(Renderable, EComponentType::Renderable);
   public:
      virtual ~Renderable();

   protected:
      Renderable(Actor* actor);

   };
}
