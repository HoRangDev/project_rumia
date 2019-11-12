#pragma once
#include <vector>
#include <string>

namespace rumia
{
	class Object;
	class World
	{
	public:
		World(const std::string& name);
		~World();

		Object* CreateObject(const std::string& name);
		Object* FindObject(const std::string& name) const;
		std::vector<Object*> FindObjects(const std::string& name) const;
		void RemoveObject(const std::string& name);
		void RemoveObjects(const std::string& name);

		void SetName(const std::string& name) { m_name = name; }
		std::string GetName() const { return m_name; }

		void Update(float dt);

	private:
		std::string				m_name;
		std::vector<Object*>	m_objects;

	};
}