#pragma once

#include "Core/EngineDefines.hpp"
#include "Core/Helper.hpp"

namespace rumia
{
	// @TODO: File Format-Resource Type Mapping
	enum class RUMIA ResourceType
	{
		Texture2D,
		Audio,
		Scene,
		Model,
		Text,
		Config,
		Unknown
	};

	class RUMIA Resource
	{
	public:
		Resource(const std::string& filePath, ResourceType resType);
		virtual ~Resource() { /* Empty Destructor */ }

		ResourceType GetType() const { return m_resType; }
		std::string GetFilePath() const { return m_filePath; }
		std::string GetFileName() const { return m_fileName; }
		std::string GetFileDirectory() const { return m_fileDirectory; }

	private:
		ResourceType	m_resType;
		std::string		m_filePath;
		std::string		m_fileName;
		std::string		m_fileDirectory;

	};
}
