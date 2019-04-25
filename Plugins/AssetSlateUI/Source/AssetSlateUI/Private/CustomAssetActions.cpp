#include "CustomAssetActions.h"

TSharedPtr<class SWidget> FCustomAssetActions::GetThumbnailOverlay(const FAssetData& AssetData) const
{
	return SNew(SImage);
}

