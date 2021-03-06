#pragma once
#include "AssetTypeActions_Base.h"

class  FTaskSequenceActions : public FAssetTypeActions_Base
{
public:
	virtual void OpenAssetEditor(const TArray<UObject*>& InObjects, TSharedPtr<class IToolkitHost> EditWithinLevelEditor = TSharedPtr<IToolkitHost>()) override;
	virtual TSharedPtr<class SWidget> GetThumbnailOverlay(const FAssetData& AssetData) const override;
	virtual FText GetName() const override;
	virtual UClass* GetSupportedClass() const;
	virtual FColor GetTypeColor() const;
	virtual uint32 GetCategories();
	virtual FText GetDisplayNameFromAssetData(const FAssetData& AssetData) const override
	{
		return FText::GetEmpty();
	}
};
