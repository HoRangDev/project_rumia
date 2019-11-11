#pragma once
#include <vector>
#include <string>
#include <typeinfo>

namespace rumia
{
	class Component;
	class Object
	{
	public:
		Object(const std::string& name);
		~Object();

		void Attach(Component* component);
		void Detach(Component* component);
		template <typename Ty>
		Ty* Detach();

		Component* FindComponent(size_t hashCode);
		template <typename Ty>
		Ty* FindComponent();
		template <typename Ty>
		std::vector<Ty*> FindComponents();

		void Update(float dt);

	private:
		std::string				m_name;
		std::vector<Component*>	m_components;

	};

	template <typename Ty>
	Ty* Object::Detach()
	{
		Ty* targetComponent = FindComponent<Ty>();
		Detach(targetComponent);
		return targetComponent;
	}

	template <typename Ty>
	Ty* Object::FindComponent()
	{
		return static_cast<Ty*>(FindComponent(typeid(Ty).hash_code()));
	}

	template <typename Ty>
	std::vector<Ty*> Object::FindComponents()
	{
		size_t hashCode = typeid(Ty).hash_code();
		std::vector<Ty*> components;
		for (auto component : m_components)
		{
			if (hashCode == typeid(*component).hash_code())
			{
				components.push_back(static_cast<Ty*>(component));
			}
		}

		return components;
	}
}