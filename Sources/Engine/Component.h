#pragma once

namespace rumia
{
	class Object;
	class Component
	{
	public:
		Component();
		virtual ~Component();

		Object* AttachedAt() const;

		virtual void Update(float dt) {}

		void SetEnable(bool enabled) { m_enabled = enabled; }
		bool IsEnabled() const { return m_enabled; }

	private:
		friend Object;
		void AttachTo(Object* target);
		void Detach();

	private:
		bool	m_enabled;
		Object* m_target;

	};
}
