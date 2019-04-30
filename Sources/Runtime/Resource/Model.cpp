#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include "Resource/Model.hpp"
#include "Resource/Material.hpp"
#include "ResourceManager.h"
#include "Rendering/StaticMesh.hpp"
#include "World/Actor.hpp"
#include "Core/Engine.hpp"

namespace rumia
{
	Model::Model() :
		Resource(EResourceType::Model)
	{
	}

	Model::~Model()
	{
		// Empty Function (Destruct meshes!)
	}

	bool Model::LoadProcess(std::ifstream& file)
	{
		file.close();

		// @TODO: Custom Flag!!
		unsigned int flags = aiProcess_Triangulate | aiProcess_FlipUVs | aiProcess_GenNormals;
		auto filePath = GetFilePath();

		Assimp::Importer importer;
		const aiScene* scene = importer.ReadFile(filePath.c_str(), flags);
		bool bIsSceneLoaded = scene != nullptr &&
			!(scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE) &&
			scene->mRootNode != nullptr;

		if (bIsSceneLoaded)
		{

			return true;
		}
		else
		{
			// @TODO: Error logs
		}

		return false;
	}

	void Model::UnloadProcess()
	{
		for (auto mesh : m_meshes)
		{
			delete mesh;
		}

		m_meshes.clear();
		m_meshes.shrink_to_fit();
		m_meshMatTable.clear();
	}

	void Model::LoadMetadataProcess(std::ifstream& metafile)
	{
		std::stringstream stream;
		stream << metafile.rdbuf();
		std::string rawJsonStr = stream.str();

		json jsonData = json::parse(rawJsonStr);
		auto meshMatTableItr = jsonData.find(MESH_MAT_TABLE_KEY);
		if (meshMatTableItr != jsonData.end())
		{
			json meshMatTable = (*meshMatTableItr);
			for (auto meshMatPair : meshMatTable)
			{
				auto meshNameItr = meshMatPair.find(MESH_NAME_KEY);
				auto materialPathItr = meshMatPair.find(MATERIAL_PATH_KEY);

				std::string meshName = meshNameItr->get<std::string>();
				std::string materialPath = materialPathItr->get<std::string>();

				auto foundItr = m_meshMatTable.find(meshName);
				bool bAlreadyExistPair = foundItr == m_meshMatTable.end();
				if (!bAlreadyExistPair)
				{
					m_meshMatTable.insert(
						std::make_pair(
							meshName,
							materialPath)
					);
				}
			}
		}
	}

	void Model::MetadataSaveProcess(std::ofstream& metafile) const
	{
		json jsonData = json::object();
		json meshMatTable = json::object();
		for (auto mesh : m_meshes)
		{
			json pair = json::object();
			Material* material = mesh->GetMaterial();

			pair[MESH_NAME_KEY] = mesh->GetName();
			pair[MATERIAL_PATH_KEY] = material->GetFilePath();
			meshMatTable.push_back(pair);
		}

		jsonData[MESH_MAT_TABLE_KEY] = meshMatTable;

		std::string dumped = jsonData.dump(4);
		metafile << jsonData;
	}

	void Model::ProcessNode(ResourceManager& resMng, aiNode* node, const aiScene* scene)
	{
		if (node != nullptr && scene != nullptr)
		{
			for (uint32 idx = 0; idx < node->mNumMeshes; ++idx)
			{
				aiMesh* importedMesh = scene->mMeshes[node->mMeshes[idx]];
				m_meshes.push_back(ProcessMesh(resMng, importedMesh, scene));
			}

			for (uint32 idx = 0; idx < node->mNumChildren; ++idx)
			{
				ProcessNode(resMng, node->mChildren[idx], scene);
			}
		}
	}

	Mesh* Model::ProcessMesh(ResourceManager& resMng, aiMesh* importedMesh, const aiScene* scene)
	{
		StaticMesh* mesh = nullptr;

		if (importedMesh != nullptr && scene != nullptr)
		{
			std::vector<VertexPTN> vertices;
			std::vector<unsigned int> indices;

			vertices.reserve(importedMesh->mNumVertices);
			// It is triangulated. So primitives are always triangle!
			indices.reserve(importedMesh->mNumFaces * 3);

			for (uint32 idx = 0; idx < importedMesh->mNumVertices; ++idx)
			{
				VertexPTN vertex;

				// Vertex Position
				vertex.Position.x = importedMesh->mVertices[idx].x;
				vertex.Position.y = importedMesh->mVertices[idx].y;
				vertex.Position.z = importedMesh->mVertices[idx].z;

				// Vertex-Normal
				vertex.Normal.x = importedMesh->mNormals[idx].x;
				vertex.Normal.y = importedMesh->mNormals[idx].y;
				vertex.Normal.z = importedMesh->mNormals[idx].z;

				// UV-Coord
				glm::vec2 texCoords{ 0.0f, 0.0f };
				if (importedMesh->mTextureCoords[0] != nullptr)
				{
					texCoords.x = importedMesh->mTextureCoords[0][idx].x;
					texCoords.y = importedMesh->mTextureCoords[0][idx].y;
				}
				vertex.TexCoord = texCoords;

				vertices.push_back(vertex);
			}

			for (uint32 idx = 0; idx < importedMesh->mNumFaces; ++idx)
			{
				aiFace face = importedMesh->mFaces[idx];
				for (uint32 vertexIdx = 0; vertexIdx < face.mNumIndices; ++vertexIdx)
				{
					indices.push_back(face.mIndices[idx]);
				}
			}

			std::string meshName = importedMesh->mName.C_Str();
			mesh = new StaticMesh(meshName, vertices, indices);
			// 만약 material table 에 mesh-material 정보가 있다면 resMng 에서 load
			// 없다면 default 로드! => 이 정보들은 metadata 에 저장!
			Material* material = nullptr;
			auto tableItr = m_meshMatTable.find(meshName);
			bool bFoundMaterial = tableItr != m_meshMatTable.end();
			if (bFoundMaterial)
			{
				material = resMng.Load<Material>((*tableItr).second);
			}
			else
			{
				material = resMng.Load<Material>(rumia::EngineDefaultMaterial);
			}

			mesh->SetMaterial(material);
		}

		return mesh;
	}

	void Model::Render(Renderer* renderer)
	{
		for (auto mesh : m_meshes)
		{
			mesh->Render(renderer);
		}
	}
}