void UModSkeletonRegistry::ScanForModPlugins()
{
	FAssetRegistryModule& AssetRegistryModule = FModuleManager::LoadModuleChecked<FAssetRegistryModule>("AssetRegistry");
	IAssetRegistry& AssetRegistry = AssetRegistryModule.Get();

	// Uncomment this and the "PakPlatform->IterateDirectoryRecursively" below to dump out pak contents on load
	//struct StructDumpVisitor : public IPlatformFile::FDirectoryVisitor
	//{
	//	virtual bool Visit(const TCHAR* FilenameOrDirectory, bool bIsDirectory)
	//	{
	//		if (bIsDirectory)
	//		{
	//			UE_LOG(ModSkeletonLog, Log, TEXT(" - DumpVisitor Directory: %s"), FilenameOrDirectory);
	//		}
	//		else
	//		{
	//			UE_LOG(ModSkeletonLog, Log, TEXT(" - DumpVisitor File: %s"), FilenameOrDirectory);
	//		}
	//		return true;
	//	}
	//};
	//StructDumpVisitor DumpVisitor;
	
	IPlatformFile& InnerPlatform = FPlatformFileManager::Get().GetPlatformFile();
	FPakPlatformFile* PakPlatform = new FPakPlatformFile();
	PakPlatform->Initialize(&InnerPlatform, TEXT(""));
	FPlatformFileManager::Get().SetPlatformFile(*PakPlatform);

	IFileManager& FileManager = IFileManager::Get();
	FString PakPath = FPaths::GameContentDir() + TEXT("Paks");
	FPaths::NormalizeDirectoryName(PakPath);
	FString BinSearch = PakPath + "/*.bin";

	// First, search for all AssetRegistry *.bin files in the Paks directory
	TArray<FString> Files;
	FileManager.FindFiles(Files, *BinSearch, true, false);
	UE_LOG(ModSkeletonLog, Log, TEXT("Searching for Pak AssetRegistries: %s"), *BinSearch);

	for (int32 i = 0; i < Files.Num(); ++i)
	{
		FString BinFilename = PakPath + TEXT("/") + Files[i];
		FPaths::MakeStandardFilename(BinFilename);
		UE_LOG(ModSkeletonLog, Log, TEXT(" - AssetRegistry: %s"), *BinFilename);

		FString PathPart;
		FString FilenamePart;
		FString ExtensionPart;
		FPaths::Split(BinFilename, PathPart, FilenamePart, ExtensionPart);
		FString PakFilename = PathPart + "/" + FilenamePart + ".pak";
		FPaths::MakeStandardFilename(PakFilename);

		if (LoadedPaks.Contains(PakFilename))
		{
			continue;
		}

		// Only process Mods that have BOTH the .bin registry and the .pak content files
		if (FPaths::FileExists(PakFilename))
		{
			UE_LOG(ModSkeletonLog, Log, TEXT("Attempting PakLoad: %s"), *PakFilename);

			// Mount the .pak content file

			// TODO - Would prefer to use this, but I cannot seem to make the mount paths correct for it
			//if (!FCoreDelegates::OnMountPak.Execute(PakFilename, 0, &DumpVisitor))
			//{
			//	UE_LOG(ModSkeletonLog, Error, TEXT("Failed to mount pak file: %s"), *PakFilename);
			//	GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Red, FString::Printf(TEXT("Failed to mount pak file: %s"), *PakFilename));
			//	continue;
			//}

			FString MountPoint(FPaths::GetPath(PakFilename));

			FPakFile PakFile(&InnerPlatform, *PakFilename, false);
			if (!PakFile.IsValid())
			{
				UE_LOG(ModSkeletonLog, Error, TEXT("Invalid pak file: %s"), *PakFilename);
				GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Red, FString::Printf(TEXT("Invalid pak file: %s"), *PakFilename));
				continue;
			}

			PakFile.SetMountPoint(*MountPoint);
			if (!PakPlatform->Mount(*PakFilename, 0, *MountPoint))
			{
				UE_LOG(ModSkeletonLog, Error, TEXT("Failed to mount pak file: %s"), *PakFilename);
				GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Red, FString::Printf(TEXT("Failed to mount pak file: %s"), *PakFilename));
				continue;
			}

			LoadedPaks.Add(PakFilename, true);

			FString MountTarget = FPaths::Combine(*MountPoint, TEXT("Plugins"), *FilenamePart, TEXT("Content/"));
			UE_LOG(ModSkeletonLog, Log, TEXT(" - Mounting At: %s"), *MountTarget);
			FPackageName::RegisterMountPoint(TEXT("/") + FilenamePart + TEXT("/"), MountTarget);

			// Load the asset registry .bin file into the in-memory AssetRegistry

			FArrayReader SerializedAssetData;
			if (FFileHelper::LoadFileToArray(SerializedAssetData, *BinFilename))
			{
				AssetRegistry.Serialize(SerializedAssetData);
				UE_LOG(ModSkeletonLog, Log, TEXT(" - AssetRegistry Loaded (%d bytes): %s"), SerializedAssetData.Num(), *BinFilename);
				//GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Emerald, FString::Printf(TEXT(" - AssetRegistry Loaded (%d bytes): %s"), SerializedAssetData.Num(), *BinFilename));
			}

			//PakPlatform->IterateDirectoryRecursively(*MountTarget, DumpVisitor);
		}
	}

	// now that the content assets have been added, and the asset registry has been updated
	// we need to search the in-memory AssetRegistry to find any MOD_SKELETON init interfaces
	
	TArray<FAssetData> AssetData;
	AssetRegistry.GetAllAssets(AssetData);

	UE_LOG(ModSkeletonLog, Log, TEXT("Searching for ModSkeleton Mod Assets:"));

	for (int32 i = 0; i < AssetData.Num(); ++i)
	{
		FString name = AssetData[i].AssetName.ToString();
		if (name.StartsWith("MOD_SKELETON", ESearchCase::CaseSensitive))
		{
			UE_LOG(ModSkeletonLog, Log, TEXT(" - Asset: %s %s %s %s"), *name, *AssetData[i].PackagePath.ToString(), *AssetData[i].ObjectPath.ToString(), *AssetData[i].AssetClass.ToString());

			if (LoadedPlugins.Contains(AssetData[i].ObjectPath))
			{
				continue;
			}

			// TODO - this is loading Blueprint Interfaces
			// make this work with C++ interfaces as well!

			UClass* AssetClass = LoadObject<UClass>(nullptr, *(TEXT("Class'") + AssetData[i].ObjectPath.ToString() + TEXT("_C'")));
			if (AssetClass != nullptr)
			{
				UObject *RealObj = NewObject<UObject>(this, AssetClass);
				if (RealObj->GetClass()->ImplementsInterface(UModSkeletonPluginInterface::StaticClass()))
				{
					// Invoke the ModSkeletonInit hook - this is invoked exactly once for every mod right at load.

					TArray< UBPVariant* > HookIO;
					IModSkeletonPluginInterface::Execute_ModSkeletonHook(RealObj, TEXT("ModSkeletonInit"), HookIO);

					LoadedPlugins.Add(AssetData[i].ObjectPath, RealObj);
				}
			}
		}
	}
}
