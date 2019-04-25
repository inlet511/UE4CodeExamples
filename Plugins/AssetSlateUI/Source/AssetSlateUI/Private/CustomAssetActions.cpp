#include "CustomAssetActions.h"
#include "AssetData.h"
#include "CustomAsset.h"
#include "CustomAssetEditorToolkit.h"
#include "DeclarativeSyntaxSupport.h"
#include "SImage.h"

#define LOCTEXT_NAMESPACE "CustomAssetActions"

TSharedPtr<class SWidget> FCustomAssetActions::GetThumbnailOverlay(const FAssetData& AssetData) const
{
	return SNew(SImage);
}

FText FCustomAssetActions::GetName() const
{
	return LOCTEXT("CustomAsset","Custom Asset");
}

uint32 FCustomAssetActions::GetCategories()
{
	return EAssetTypeCategories::UI;
}

UClass* FCustomAssetActions::GetSupportedClass() const
{
	return UCustomAsset::StaticClass();
}

FColor FCustomAssetActions::GetTypeColor() const
{
	return FColor::Purple;
}

void FCustomAssetActions::OpenAssetEditor(const TArray<UObject*>& InObjects, TSharedPtr<class IToolkitHost> EditWithinLevelEditor /*= TSharedPtr<IToolkitHost>()*/)
{
	EToolkitMode::Type Mode = EditWithinLevelEditor.IsValid() ? EToolkitMode::WorldCentric : EToolkitMode::Standalone;
	for (auto ObjIt = InObjects.CreateConstIterator(); ObjIt; ++ObjIt)
	{
		auto CustomAsset = Cast<UCustomAsset>(*ObjIt);
		if (CustomAsset != nullptr)
		{
			TSharedRef<FCustomAssetEditorToolkit> EditorToolKit = MakeShareable(new FCustomAssetEditorToolkit());
			EditorToolKit->Initialize(CustomAsset, Mode, EditWithinLevelEditor);
		}
	}
}

#undef LOCTEXT_NAMESPACE