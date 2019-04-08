 void UNigisUtils::MountPakAndStartAssetLoading(const FString & PakFolder, const FString& PakName, const FString& MountPoint, TArray<FString>& AssetStrings, bool bSyncPreloadAssets)
 {
     UE_LOG(LogTemp, Log, TEXT("============= START LOADING PAK ============="));
     if (!PakFolder.IsEmpty() && !PakName.IsEmpty() && PakName.Right(3).Equals(TEXT("pak"), ESearchCase::IgnoreCase))
     {
         IPlatformFile* PreviousPlatformFile = nullptr;
         FPakPlatformFile *PlatformFile = nullptr;
         if (FString(FPlatformFileManager::Get().GetPlatformFile().GetName()).Equals(FString(TEXT("PakFile"))))
         {
             PlatformFile = static_cast<FPakPlatformFile*>(&FPlatformFileManager::Get().GetPlatformFile());
         }
         else
         {
             PlatformFile = new FPakPlatformFile();
 
             if (!PlatformFile->Initialize(&FPlatformFileManager::Get().GetPlatformFile(), TEXT("")))
             {
                 UE_LOG(LogTemp, Error, TEXT("FPakPlatformFile failed to initialize"));
                 return;
             }
             PreviousPlatformFile = &FPlatformFileManager::Get().GetPlatformFile();
             FPlatformFileManager::Get().SetPlatformFile(*PlatformFile);
         }
 
         FString FullPakFolder(FPaths::ConvertRelativePathToFull(PakFolder));
         if (!PlatformFile->DirectoryExists(*FullPakFolder))
         {
             UE_LOG(LogTemp, Error, TEXT("Directory not found: %s"), *FullPakFolder);
             return;
         }
         else UE_LOG(LogTemp, Warning, TEXT("Pak folder verified: %s"), *FullPakFolder);
 
         if (FCoreDelegates::OnMountPak.IsBound())
         {
             // Print files in pak
             struct FilesDump : public IPlatformFile::FDirectoryVisitor
             {
                 FString mp_PakName;
                 TArray<FString> Files;
 
                 FilesDump(FString &PakfileName)
                     : mp_PakName(PakfileName)
                 {}
 
                 virtual bool Visit(const TCHAR *FilenameOrDirectory, bool bIsDirectory)
                 {
                     if (bIsDirectory)
                     {
                         UE_LOG(LogTemp, Log, TEXT("Found DIR in %s: %s"), *mp_PakName, FilenameOrDirectory);
                     }
                     else
                     {
                         const FString Filename(FilenameOrDirectory);
                         if (Filename.Contains(TEXT(".umap")) || Filename.Contains(TEXT(".uasset")))
                         {
                             Files.Add(FilenameOrDirectory);
                             UE_LOG(LogTemp, Log, TEXT("Found FILE in %s: %s"), *mp_PakName, FilenameOrDirectory);
                         }
                     }
                     return true;
                 }
             };
 
             FString PakfileName = PakName;
             FilesDump Visitor(PakfileName);
             FString FullPath = FPaths::Combine(PakFolder, PakName);
 
             FPakFile PakFile(PlatformFile, *FullPath, false);
             if (PakFile.IsValid())
             {
                 FString InMountPoint = MountPoint;
                 FPaths::MakePathRelativeTo(InMountPoint, *FPaths::ProjectContentDir());
                 InMountPoint = FString("/Game/" + InMountPoint);
 
                 PakFile.SetMountPoint(*InMountPoint);
                 //if (PlatformFile->Mount(*FullPath, 4, *InMountPoint))
                 if(FCoreDelegates::OnMountPak.Execute(FullPath, 4, &Visitor))
                 {
                     UE_LOG(LogTemp, Log, TEXT("Pak Mount success!"));    
                     UE_LOG(LogTemp, Warning, TEXT("Reading Pak Contents..."));
                     LoadedAssets.Empty();
 
                     TArray<FString> Files;
                     PakFile.FindFilesAtPath(Files, *InMountPoint, true, false, true);
 
                     //PlatformFile->IterateDirectoryRecursively(*MountPoint, Visitor);
 
                     UE_LOG(LogTemp, Warning, TEXT("\n Generating Asset References..."));
                     TArray<FSoftObjectPath> ObjectPaths;
                     UE_LOG(LogTemp, Log, TEXT("------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------"));
                     for (FString File : Files)
                     {
                         FString Filename, FileExtn;
                         int32 LastSlashIndex;
                         File.FindLastChar(*TEXT("/"), LastSlashIndex);
                         FString FileOnly = File.RightChop(LastSlashIndex + 1); //remove the full size since we want the slash gone too.
                         UE_LOG(LogTemp, Log, TEXT("File: %s ============ Full Path: %s"), *FileOnly, *File);
                         FileOnly.Split(TEXT("."), &Filename, &FileExtn);
 
                         if (FileExtn == TEXT("uasset"))
                         {
                             File = File.Replace(TEXT("uasset"), *Filename);
                             /*int32 ContentFolderIndex = File.Find(TEXT("/Content"), ESearchCase::Type::CaseSensitive, ESearchDir::Type::FromEnd);
                             FString RelativePath = File.RightChop(ContentFolderIndex + 8);
                             FString AssetPath("/Game" + RelativePath);*/
 
                             FStringAssetReference AssetRef(*File);
                             Assets.Add(TAssetPtr<UObject>(AssetRef));
                             AssetStrings.Add(File);
 
                             //Add a soft object path to the list
                             FSoftObjectPath SoftObjectPath(File);
                             ObjectPaths.Add(SoftObjectPath);
                             SOPtrs.Add(TSoftObjectPtr<UObject>(SoftObjectPath));
 
                             UE_LOG(LogTemp, Log, TEXT("File: %s, Asset reference: %s"), *FileOnly, *AssetRef.ToString());
                         } else UE_LOG(LogTemp, Log, TEXT("File: %s is not an asset file. No reference generated."), *FileOnly)
                         
                         UE_LOG(LogTemp, Log, TEXT("------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------"));
                     }
                     UE_LOG(LogTemp, Warning, TEXT("\n %d references Generated."), ObjectPaths.Num());
 
                     //Optionally synchronously loads all the references found in the pak
                     if (bSyncPreloadAssets)
                     {
                         UE_LOG(LogTemp, Warning, TEXT("\n Attempting to syncronous load generated references..."));
                         for (const FSoftObjectPath ObjectPath : ObjectPaths)
                         {
                             UObject* LoadedAsset = ObjectPath.TryLoad();
                             if (LoadedAsset != nullptr)
                             {
                                 UE_LOG(LogTemp, Log, TEXT("Asset Reference: %s, Succesfully loaded!"), *ObjectPath.ToString());
                                 LoadedAssets.Add(LoadedAsset);
                             }
                             else UE_LOG(LogTemp, Error, TEXT("Asset Reference: %s, load failed."), *ObjectPath.ToString());
                         }
                         OnAssetsLoadComplete.Broadcast(LoadedAssets);
                     }
                     else
                     {
                         UE_LOG(LogTemp, Warning, TEXT("\n Starting Async load of assets..."));
                         StreamManager.RequestAsyncLoad(ObjectPaths, FStreamableDelegate::CreateUObject(this, &UNigisUtils::ObjectsLoadingComplete));
                     }
                 }
                 else UE_LOG(LogTemp, Error, TEXT("Pak Mount failed."));
             }
             
         }
         else UE_LOG(LogTemp, Error, TEXT("\"OnMountPak\" Core delegate is not bound."));
 
         // return previous platform file manager to the top of the chain, so Unreal doesn't lose it's references
         if (PreviousPlatformFile != nullptr)
         {
             FPlatformFileManager::Get().SetPlatformFile(*PreviousPlatformFile);
         }
     }
     UE_LOG(LogTemp, Log, TEXT("============= END LOADING PAK ============="));
 }