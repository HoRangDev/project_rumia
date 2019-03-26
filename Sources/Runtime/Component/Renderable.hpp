#pragma once
#include "Component/Component.hpp"

namespace rumia
{
   class RUMIA Renderable : public Component
   {
      RUMIA_COMPONENT(Renderable, EComponentType::Renderable);
   public:
      virtual ~Renderable();

      virtual json Serialize() const { return json(); }
      virtual void DeSerialize(const json& object) { }

   protected:
      Renderable(Actor* actor);

   };
}
