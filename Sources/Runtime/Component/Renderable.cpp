#include "Renderable.h"

namespace rumia
{
   RUMIA_REGISTER_COMPONENT(Renderable);

   Renderable::Renderable(Actor* actor) :
      Component(actor)
   {
   }

   Renderable::~Renderable()
   {
   }
}