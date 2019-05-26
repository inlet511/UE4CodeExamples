#pragma once
#include "CoreMinimal.h"
#include "Toolkits/AssetEditorToolkit.h"
#include "Task.h"

class FTaskEditorToolkit : public FAssetEditorToolkit
{
public:
	virtual void RegisterTabSpawners(const TSharedRef<FTabManager>& InTabManager) override;
	virtual void UnregisterTabSpawners(const TSharedRef<FTabManager>& InTabManager) override;
	virtual FName GetToolkitFName() const override;		  // Must implement in derived class!
	virtual FText GetBaseToolkitName() const override;	// Must implement in derived class!
	virtual FString GetWorldCentricTabPrefix() const override;	// Must implement in derived class!
	virtual FLinearColor GetWorldCentricTabColorScale(void) const override;

	void Initialize(UTask* InTaskAsset, const EToolkitMode::Type InMode, const TSharedPtr<IToolkitHost>& InToolkitHost);

private:
	UTask* EditingTask;
};