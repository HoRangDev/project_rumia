#include "StaticMesh.hpp"

namespace rumia
{
	StaticMesh::StaticMesh(const std::string& meshName, const std::vector<VertexPTN>& vertices, const std::vector<uint32>& indices) :
		m_vertices(vertices),
		m_indices(indices),
		m_vao(0),
		m_ebo(0),
		m_vbo(0),
		Mesh(meshName)
	{
	   Initialize();
	}

		bool StaticMesh::Initialize_Impl()
	{
		glGenVertexArrays(1, &m_vao);
		glGenBuffers(1, &m_vbo);
		glGenBuffers(1, &m_ebo);

		glBindVertexArray(m_vao);
		glBindBuffer(GL_ARRAY_BUFFER, m_vbo);

		glBufferData(GL_ARRAY_BUFFER,
			sizeof(VertexPTN) * m_vertices.size(),
			m_vertices.data(),
			GL_STATIC_DRAW);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ebo);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER,
			sizeof(uint32) * m_indices.size(),
			m_indices.data(),
			GL_STATIC_DRAW);

		glEnableVertexArrayAttrib(m_vao, 0);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(VertexPTN), (void*)0);

		glEnableVertexArrayAttrib(m_vao, 1);
		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(VertexPTN), (void*)offsetof(VertexPTN, VertexPTN::TexCoord));

		glEnableVertexArrayAttrib(m_vao, 2);
		glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(VertexPTN), (void*)offsetof(VertexPTN, VertexPTN::Normal));

		glBindVertexArray(0);

		return true;
	}

	void StaticMesh::Render_Impl(Renderer* renderer)
	{
		glBindVertexArray(m_vao);
		glDrawElements(GL_TRIANGLES, m_indices.size(), GL_UNSIGNED_INT, nullptr);
		glBindVertexArray(0);
	}
}