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

         std::ifstream fileStream;
         std::ifstream metafileStream;
         fileStream.open(m_filePath);
         if (fileStream.is_open())
         {
            metafileStream.open(m_metafilePath);
			if (metafileStream.is_open()) 
			{
				LoadMetadataProcess(metafileStream);
			}

            m_bLoaded = LoadProcess(fileStream);
         }

         fileStream.close();
         metafileStream.close();
      }

      return m_bLoaded;
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
      std::ofstream fileStream;
      fileStream.open(filePath, std::ios::trunc);
      if (fileStream.is_open())
      {
         SaveProcess(fileStream);
         fileStream.close();
      }

      std::ofstream metafileStream;
      metafileStream.open(m_metafilePath, std::ios::trunc);
      if (metafileStream.is_open())
      {
         MetadataSaveProcess(metafileStream);
         metafileStream.close();
      }
   }

   void Resource::Save() const
   {
      SaveAs(m_filePath);
   }
}