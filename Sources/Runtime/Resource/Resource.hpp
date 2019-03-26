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

		virtual bool Load() final;
		virtual void Unload() final;
		virtual bool Reload() final;

		virtual bool LoadProcess() = 0;
		virtual void UnloadProcess() = 0;

	private:
		void IncreaseRefCount() { ++m_refCount; }
		void DecreaseRefCount() { --m_refCount; }

	private:
		ResourceType	m_resType;
		std::string		m_filePath;
		std::string		m_fileName;
		std::string		m_fileDirectory;

		bool			m_bLoaded;
		uint64			m_refCount;

	};
}
