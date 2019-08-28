// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Modules/ModuleManager.h"

class FToolBarBuilder;
class FMenuBuilder;

class FErgonomicsEditorModule : public IModuleInterface
{
public:

	/** IModuleInterface implementation */
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;
	
	/** This function will be bound to Command (by default it will bring up plugin window) */
	void PluginButtonClicked(const FName TabName);


	//当前编辑器中在编辑的几种算法对象
	TSharedPtr<class NIOSH> EditingNIOSH;
	TSharedPtr<class REBA>  EditingREBA;
	TSharedPtr<class RULA>  EditingRULA;
	TSharedPtr<class WISHA> EidtingWISHA;
	TSharedPtr<class Snook> EditingSnook;

	//初始化算法对象
	void InitAlgorithmObject();
	
private:

	void AddToolbarExtension(FToolBarBuilder& Builder);
	void AddMenuExtension(FMenuBuilder& Builder);

	TSharedRef<class SDockTab> OnSpawnTab_NIOSH(const class FSpawnTabArgs& SpawnTabArgs);
	TSharedRef<class SDockTab> OnSpawnTab_REBA(const class FSpawnTabArgs& SpawnTabArgs);
	TSharedRef<class SDockTab> OnSpawnTab_RULA(const class FSpawnTabArgs& SpawnTabArgs);
	TSharedRef<class SDockTab> OnSpawnTab_WISHA(const class FSpawnTabArgs& SpawnTabArgs);
	TSharedRef<class SDockTab> OnSpawnTab_Snook(const class FSpawnTabArgs& SpawnTabArgs);

	TSharedPtr<class FUICommandList> PluginCommands;

	static TSharedRef<class SWidget> GenerateErgonomicsToolBarMenu(TSharedRef<class FUICommandList> InCommandList);
};