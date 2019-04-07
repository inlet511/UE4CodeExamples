bool DLCDownloadManager::MountPak(const FString &rPakFileName, DLCMountPointInfo &rMPI)
 {
      //Load and mount pak file
     if (mp_DLCPakFiles == nullptr)
     {
         mp_DLCPakFiles = new FPakPlatformFile;
         if (!mp_DLCPakFiles->Initialize(&FPlatformFileManager::Get().GetPlatformFile(), TEXT("")))
         {
               return false;
         }
 
         mp_DLCPakFiles->InitializeNewAsyncIO();
         
         FPlatformFileManager::Get().SetPlatformFile(*mp_DLCPakFiles);
     }
 
     FString StandardFilename(rPakFileName);
     FPaths::MakeStandardFilename(StandardFilename);
     StandardFilename = FPaths::GetPath(StandardFilename);
     
     if (!mp_DLCPakFiles->Mount(*rPakFileName, 0, *StandardFilename))
     {
          return false;
     }
 
     static int siMountIndex = 0;
     rMPI.m_Directory = StandardFilename;
     rMPI.m_MountPoint = FString::Printf(_T("/DLC%d/"), siMountIndex++);
     FPackageName::RegisterMountPoint(rMPI.m_MountPoint, StandardFilename);
 
 #if 0 //Enable to dump files and directories while debugging
     struct Dump : public IPlatformFile::FDirectoryVisitor
     {
         virtual bool Visit(const TCHAR* FilenameOrDirectory, bool bIsDirectory)
         {
                 SysOutputf(DownloadManager, bIsDirectory ? _T("Directory: %s") : _T("File: %s"), FilenameOrDirectory);
             return true;
         }
     };
     Dump visitor;
     mp_DLCPakFiles->IterateDirectoryRecursively(*StandardFilename, visitor);
 #endif
 
     return true;
 }
 