#pragma once
#include "Component.h"
#include <iostream>

namespace rumia
{
	class EmptyComponent : public Component
	{
	public:
		EmptyComponent(int idx) :
			m_index(idx)
		{
		}

		~EmptyComponent() 
		{
		}

		virtual void Update(float dt) override
		{
			std::cout << "Update!" << m_index << std::endl;
		}

		int GetIndex() const { return m_index; }

	private:
		int	m_index;

	};
}