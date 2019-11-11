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

	private:
		friend Object;
		void AttachTo(Object* target);
		void Detach();

	private:
		Object* m_target;

	};
}
