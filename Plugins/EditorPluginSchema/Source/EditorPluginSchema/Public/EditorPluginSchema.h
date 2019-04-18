// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Modules/ModuleManager.h"

class FToolBarBuilder;
class FMenuBuilder;

class FEditorPluginSchemaModule : public IModuleInterface
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
	void AddMenuBarExtension(FMenuBarBuilder& Builder);
	void AddMenuBarPulldown(FMenuBarBuilder& Builder);

	void PullDownBar(FMenuBuilder& Builder);
	void SubMenuBar(FMenuBuilder& Builder);

private:
	TSharedPtr<class FUICommandList> PluginCommands;
};

class FTestABC
{
	public:
	static TSharedRef<SWidget> MakeWidget(TSharedPtr<class FUICommandList> PluginCommands);
};