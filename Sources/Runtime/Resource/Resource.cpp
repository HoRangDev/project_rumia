#include "Resource/Resource.hpp"

namespace rumia
{
	Resource::Resource(const std::string& filePath, ResourceType resType) :
		m_resType(resType),
		m_filePath(filePath),
		m_bLoaded(false),
		m_refCount(0)
	{
		auto splitedPath = helper::SplitString(m_filePath, { '/', '\\' });
		m_fileName = splitedPath[splitedPath.size() - 1];
		splitedPath.pop_back();

		m_fileDirectory = helper::CombineString(splitedPath, "/");
		//@TODO: split file path to name and directory then stored at each variables
	}

	Resource::~Resource()
	{
		// Double check
		Unload();
	}

	bool Resource::Load()
	{
		if (!m_bLoaded)
		{
			return LoadProcess();
		}

		return false;
	}

	void Resource::Unload()
	{
		if (m_bLoaded)
		{
			UnloadProcess();
		}
	}

	bool Resource::Reload()
	{
		Unload();
		return Load();
	}
}