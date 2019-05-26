#pragma once
#include "CoreMinimal.h"
#include "Toolkits/AssetEditorToolkit.h"

class FRescurePhaseToolkit : public FAssetEditorToolkit
{
public:
	virtual void RegisterTabSpawners(const TSharedRef<FTabManager>& TabManager) override;
	virtual void UnregisterTabSpawners(const TSharedRef<FTabManager>& TabManager) override;
	virtual FName GetToolkitFName() const override = 0;		  // Must implement in derived class!
	virtual FText GetBaseToolkitName() const override = 0;	// Must implement in derived class!
	virtual FString GetWorldCentricTabPrefix() const override = 0;	// Must implement in derived class!
};