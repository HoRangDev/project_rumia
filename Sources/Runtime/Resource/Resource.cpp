#include "Resource/Resource.hpp"

namespace rumia
{
	Resource::Resource(EResourceType resType) :
		m_resType(resType),
		m_bLoaded(false),
		m_refCount(0)
	{
		
	}

	Resource::~Resource()
	{
		// Double check
		Unload();
	}

	bool Resource::Load(const std::string& filePath)
	{
		if (!m_bLoaded)
		{
           m_filePath = filePath;

           auto splitedPath = helper::SplitString(m_filePath, { '/', '\\' });
           m_fileName = splitedPath[splitedPath.size() - 1];
           splitedPath.pop_back();

           m_fileDirectory = helper::CombineString(splitedPath, "/");

           auto splitedName = helper::SplitString(m_fileName, '.');
           m_fileExt = splitedName[splitedName.size() - 1];

           std::string metafileName = m_filePath;
           metafileName.append(MetafileExtension);
           m_metafilePath = m_fileDirectory;
           m_metafilePath.append(FileDirectorySeparator);
           m_metafilePath.append(metafileName);

           m_bLoaded = LoadProcess();
           LoadMetadataProcess();
           return m_bLoaded;
		}

		return false;
	}

	void Resource::Unload()
	{
		if (m_bLoaded)
		{
			UnloadProcess();
            m_bLoaded = false;
		}
	}

	bool Resource::Reload()
	{
		Unload();
		return Load(m_filePath);
	}

    void Resource::SaveAs(const std::string& filePath) const
    {
       if (m_bLoaded)
       {
          std::ofstream fileStream{ filePath.c_str() };
          SaveProcess(fileStream);
          fileStream.close();

          std::ofstream metafileStream{ metafilePath.c_str() };
          MetadataSaveProcess(metafileStream);
          metafileStream.close();
       }
    }

    void Resource::Save() const
    {
       SaveAs(m_filePath);
    }
}