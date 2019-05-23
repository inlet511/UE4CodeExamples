#pragma once
#include "CoreMinimal.h"
#include "Toolkits/AssetEditorToolkit.h"

class FTaskSequenceEditorToolkit : public FAssetEditorToolkit
{
public:
	virtual void RegisterTabSpawners(const TSharedRef<FTabManager>& TabManager) override;
	virtual void UnregisterTabSpawners(const TSharedRef<FTabManager>& TabManager) override;
	virtual FName GetToolkitFName() const override;		  // Must implement in derived class!
	virtual FText GetBaseToolkitName() const override;	// Must implement in derived class!
	virtual FString GetWorldCentricTabPrefix() const override;	// Must implement in derived class!
};