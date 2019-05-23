// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Modules/ModuleManager.h"
#include "Task.h"
#include "AssetTypeCategories.h"

class FToolBarBuilder;
class FMenuBuilder;

static EAssetTypeCategories::Type ContigencyCategory;

class FContigencyPlanEditorModule : public IModuleInterface
{
public:

	/** IModuleInterface implementation */
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;
	
	/** This function will be bound to Command. */
	void PluginButtonClicked();
	
private:

	void AddToolbarExtension(FToolBarBuilder& Builder);
	void AddMenuExtension(FMenuBuilder& Builder);

private:
	TSharedPtr<class FUICommandList> PluginCommands;
	TArray<TSharedRef<class IAssetTypeActions>> RegisteredAssetTypeActions;
};
