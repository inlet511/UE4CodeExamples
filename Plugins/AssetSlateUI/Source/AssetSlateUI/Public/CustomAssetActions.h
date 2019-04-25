#pragma once
#include "AssetTypeActions_Base.h"

class FCustomAssetActions :public FAssetTypeActions_Base
{
public:
	virtual TSharedPtr<class SWidget> GetThumbnailOverlay(const FAssetData& AssetData) const override;

};