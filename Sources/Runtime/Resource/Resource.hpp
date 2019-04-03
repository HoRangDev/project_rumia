#pragma once

#include "Core/EngineDefines.hpp"
#include "Core/Helper.hpp"

#include <fstream>
#include <sstream>
#include <iostream>

namespace rumia
{
	// @TODO: File Format-Resource Type Mapping
	enum class RUMIA EResourceType
	{
		Texture,
        Model,
        Shader,
        Material,
		Audio,
		Scene,
		Text,
		Config,
		Unknown
	};

	class RUMIA Resource
	{
	public:
		Resource(EResourceType resType);
		virtual ~Resource();

        EResourceType GetType() const { return m_resType; }
		std::string GetFilePath() const { return m_filePath; }
		std::string GetFileName() const { return m_fileName; }
        std::string GetFileExt() const { return m_fileExt; }
		std::string GetFileDirectory() const { return m_fileDirectory; }

		uint64 GetRefCount() const { return m_refCount; }

		virtual bool Load(const std::string& filePath) final;
		virtual void Unload() final;
		virtual bool Reload() final;

        bool IsLoaded() const { return m_bLoaded; }

		virtual bool LoadProcess(std::ifstream& file) = 0;
        virtual void LoadMetadataProcess(std::ifstream& metafile){}
		virtual void UnloadProcess() = 0;

        virtual void SaveProcess(std::ofstream& file) const = 0;
        virtual void MetadataSaveProcess(std::ofstream& metafile) const {}
        virtual void SaveAs(const std::string& filePath) const final;
        virtual void Save() const final;

		//@TODO: Add Metadata

	private:
		void IncRefCount() { ++m_refCount; }
		void DecRefCount() { --m_refCount; }
        friend class ResourceManager;

	private:
        EResourceType	m_resType;
		std::string		m_filePath;
		std::string		m_fileName;
        std::string     m_fileExt;
		std::string		m_fileDirectory;

        std::string     m_metafilePath;

		bool			m_bLoaded;
		uint64			m_refCount;

	};
}
