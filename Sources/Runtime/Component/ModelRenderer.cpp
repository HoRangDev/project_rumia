#include "ModelRenderer.hpp"

namespace rumia
{
	RUMIA_REGISTER_COMPONENT(ModelRenderer);

	ModelRenderer::ModelRenderer(Actor* actor) :
		m_model(nullptr),
		Renderable(actor)
	{
	}

	ModelRenderer::~ModelRenderer()
	{
	}

	void ModelRenderer::SetModel(Model* model)
	{
		m_model = model;
	}

	/*void ModelRenderer::Render(Renderer* renderer)
	{
	//@TODO: Implement Renderer
	}*/
}