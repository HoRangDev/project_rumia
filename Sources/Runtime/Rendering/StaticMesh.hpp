#pragma once
#include "Rendering/Mesh.hpp"

namespace rumia
{
	struct RUMIA VertexPTN
	{
		glm::vec3 Position;
		glm::vec2 TexCoord;
		glm::vec3 Normal;
	};

	class RUMIA StaticMesh : public Mesh
	{
	public:
		StaticMesh(const std::string& meshName, const std::vector<VertexPTN>& vertices, const std::vector<uint32>& indices);

		GLuint GetVAO() const { return m_vao; }
		GLuint GetVBO() const { return m_vbo; }
		GLuint GetEBO() const { return m_ebo; }

	private:
		virtual bool Initialize_Impl() override;
		virtual void Render_Impl(Renderer* renderer) override;

	private:
		std::vector<VertexPTN>           m_vertices;
		std::vector<uint32>              m_indices;

		GLuint   m_vao;
		GLuint   m_vbo;
		GLuint   m_ebo;

	};
}