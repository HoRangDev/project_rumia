#include "Component.h"

namespace rumia
{
	Component::Component() : 
		m_target(nullptr)
	{
	}

	Component::~Component()
	{
		m_target = nullptr;
	}

	Object* Component::AttachedAt() const
	{
		return m_target;
	}

	void Component::AttachTo(Object* target)
	{
		m_target = target;
	}

	void Component::Detach()
	{
		m_target = nullptr;
	}
}