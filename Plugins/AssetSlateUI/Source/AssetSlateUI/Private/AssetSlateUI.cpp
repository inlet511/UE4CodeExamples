// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.

#include "AssetSlateUI.h"
#include "Modules/ModuleManager.h"
#include "AssetToolsModule.h"
#include "IAssetTools.h"
#include "CustomAssetActions.h"

#define LOCTEXT_NAMESPACE "FAssetSlateUIModule"

void FAssetSlateUIModule::StartupModule()
{
	IAssetTools& AssetTools = FModuleManager::LoadModuleChecked<FAssetToolsModule>("AssetTools").Get();
	RegisteredAssetTypeActions.Add(MakeShareable(new FCustomAssetActions()));
	AssetTools.RegisterAssetTypeActions(RegisteredAssetTypeActions[RegisteredAssetTypeActions.Num()-1]);
}

void FAssetSlateUIModule::ShutdownModule()
{
	FAssetToolsModule* AssetToolsModule = FModuleManager::GetModulePtr<FAssetToolsModule>("AssetTools");
	if (AssetToolsModule != nullptr)
	{
		IAssetTools& AssetTools = AssetToolsModule->Get();
		for (auto Action : RegisteredAssetTypeActions)
		{
			AssetTools.UnregisterAssetTypeActions(Action);
		}
	}
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FAssetSlateUIModule, AssetSlateUI)