#pragma once
#include "Renderable.hpp"

namespace rumia
{
	class Model;
	class ModelRenderer : public Renderable
	{
		RUMIA_COMPONENT(ModelRenderer, EComponentType::Renderable);
	public:
		ModelRenderer(Actor* actor);
		virtual ~ModelRenderer();

		virtual void Render(Renderer* renderer) override;

		void SetModel(Model* model);
		Model* GetModel() const { return m_model; }

	private:
		Model* m_model;

	};
}
