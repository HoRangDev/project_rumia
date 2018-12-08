#include "Actor.hpp"
#include "Component/Transform.hpp"

namespace rumia
{
   unsigned int Actor::staticIDCount = 0;

   Actor::Actor(const std::string& name) :
      m_bEnabled(true),
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
      for (int idx = 0; idx < m_components.size(); ++idx)
      {
         delete m_components[idx];
      }
      m_components.clear();
   }
}