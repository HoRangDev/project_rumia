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

		uint64 GetRefCount() const { return m_refCount; }

	private:
		void IncreaseRefCount() { ++m_refCount; }
		void DecreaseRefCount() { --m_refCount; }

	private:
		ResourceType	m_resType;
		std::string		m_filePath;
		std::string		m_fileName;
		std::string		m_fileDirectory;

		uint64			m_refCount;

	};
}
