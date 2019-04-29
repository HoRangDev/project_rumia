#pragma once
#include "Resource/Resource.hpp"
#include <unordered_map>

class aiNode;
class aiScene;
class aiMesh;

namespace rumia
{
	// @TODO: Mesh -> Actor convert
	// Model meta data:
	// Model file/mesh type/preprocess flags/mesh-material table
	class Renderer;
	class Mesh;
	class Actor;
	class RUMIA Model : public Resource
	{
	public:
		Model();
		~Model();

		virtual bool LoadProcess(std::ifstream& file) override;
		virtual void UnloadProcess() override;

		//@TODO: Impl save model files
		virtual void SaveProcess(std::ofstream& file) const override { /* Empty */ }

		void Render(Renderer* renderer);

	private:
		void ProcessNode(class ResourceManager& resMng, aiNode* node, const aiScene* scene);
		Mesh* ProcessMesh(class ResourceManager& resMng, aiMesh* importedMesh, const aiScene* scene);

	private:
		std::vector<Mesh*>      m_meshes;
		std::unordered_map<std::string, std::string> m_meshMatTable;

	};
}