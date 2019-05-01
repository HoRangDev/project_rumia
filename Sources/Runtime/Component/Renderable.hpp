#pragma once
#include "Component/Component.hpp"

namespace rumia
{
	class Renderer;
	class RUMIA Renderable : public Component
	{
		RUMIA_ABSTRACT_COMPONENT(Renderable)
	public:
		virtual ~Renderable();

		virtual json Serialize() const { return json(); }
		virtual void DeSerialize(const json& object) { }

		virtual void Render(Renderer* renderer) =0;

	protected:
		Renderable(Actor* actor);

	};
}
