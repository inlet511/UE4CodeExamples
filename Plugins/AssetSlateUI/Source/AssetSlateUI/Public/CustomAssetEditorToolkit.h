#pragma once
#include "CustomAsset.h"
#include "Toolkits/AssetEditorToolkit.h"

class FCustomAssetEditorToolkit : public FAssetEditorToolkit
{
	typedef FAssetEditorToolkit Super;

public:
	virtual void RegisterTabSpawners(const TSharedRef<FTabManager>& InTabManager) override;
	virtual void UnregisterTabSpawners(const TSharedRef<FTabManager>& InTabManager) override;
	virtual FName GetToolkitFName() const override;		  // Must implement in derived class!
	virtual FText GetBaseToolkitName() const override;	// Must implement in derived class!
	virtual FString GetWorldCentricTabPrefix() const override;	// Must implement in derived class!
	virtual FLinearColor GetWorldCentricTabColorScale(void) const override;

	void Initialize(UCustomAsset* InTextAsset, const EToolkitMode::Type InMode, const TSharedPtr<IToolkitHost>& InToolkitHost);

private:
	UCustomAsset* InCustomAsset;
};