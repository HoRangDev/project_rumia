#include "Object.h"
#include "Component.h"

namespace rumia
{
	Object::Object(const std::string& name) :
		m_name(name)
	{
	}

	Object::~Object()
	{
		for (auto* component : m_components)
		{
			delete component;
		}

		m_components.clear();
	}

	void Object::Attach(Component* component)
	{
		if (component != nullptr)
		{
			Object* pastTarget = component->AttachedAt();
			if (pastTarget == nullptr)
			{
				component->AttachTo(this);
				m_components.push_back(component);
			}
		}
	}

	void Object::Detach(Component* component)
	{
		if (component != nullptr)
		{
			for (auto itr = m_components.begin(); itr != m_components.end(); ++itr)
			{
				Component* founded = (*itr);
				if (component == founded)
				{
					component->Detach();
					m_components.erase(itr);
					break;
				}
			}
		}
	}

	Component* Object::FindComponent(size_t hashCode)
	{
		for (auto* component : m_components)
		{
			if (typeid(*component).hash_code() == hashCode)
			{
				return component;
			}
		}

		return nullptr;
	}

	void Object::Update(float dt)
	{
		for (auto component : m_components)
		{
			component->Update(dt);
		}
	}
}