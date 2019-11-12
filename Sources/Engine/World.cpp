#include "World.h"
#include "Object.h"

namespace rumia
{
	World::World(const std::string& name) :
		m_name(name)
	{
	}

	World::~World()
	{
		for (auto* object : m_objects)
		{
			delete object;
		}
		m_objects.clear();
	}

	Object* World::CreateObject(const std::string& name)
	{
		// @TODO: Transform 컴포넌트를 기본적으로 새로운 오브젝트에 추가시키기
		Object* newObject = new Object(name);
		m_objects.push_back(newObject);
		return newObject;
	}

	Object* World::FindObject(const std::string& name) const
	{
		for (auto object : m_objects)
		{
			if (object != nullptr)
			{
				if (object->GetName() == name)
				{
					return object;
				}
			}
		}

		return nullptr;
	}

	std::vector<Object*> World::FindObjects(const std::string& name) const
	{
		std::vector<Object*> founded;
		for (auto object : m_objects)
		{
			if (object != nullptr)
			{
				if (object->GetName() == name)
				{
					founded.push_back(object);
				}
			}
		}

		return founded;
	}

	void World::RemoveObject(const std::string& name)
	{
		for (auto itr = m_objects.begin(); itr != m_objects.end();
			++itr)
		{
			Object* founded = (*itr);
			if (founded->GetName() == name)
			{
				m_objects.erase(itr);
				delete founded;
				return;
			}
		}
	}

	void World::RemoveObjects(const std::string& name)
	{
		for (auto itr = m_objects.begin(); itr != m_objects.end();
			++itr)
		{
			Object* founded = (*itr);
			if (founded->GetName() == name)
			{
				itr = m_objects.erase(itr);
				delete founded;
				founded = nullptr;
			}
		}
	}

	void World::Update(float dt)
	{
		for (auto object : m_objects)
		{
			if (object->IsEnabled())
			{
				object->Update(dt);
			}
		}
	}
}