#pragma once
#include "AssetTypeActions_Base.h"

class FCustomAssetActions :public FAssetTypeActions_Base
{
public:
	virtual TSharedPtr<class SWidget> GetThumbnailOverlay(const FAssetData& AssetData) const override;
	virtual FText GetName() const override;
	virtual uint32 GetCategories() override;
	virtual UClass* GetSupportedClass() const;
	virtual FColor GetTypeColor() const;
	virtual void OpenAssetEditor(const TArray<UObject*>& InObjects, TSharedPtr<class IToolkitHost> EditWithinLevelEditor = TSharedPtr<IToolkitHost>()) override;
};