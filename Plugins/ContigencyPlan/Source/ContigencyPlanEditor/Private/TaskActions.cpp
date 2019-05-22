#include "TaskActions.h"
#include "Task.h"
#include "TaskEditorToolkit.h"
#include "ContigencyPlanEditor.h"
#include "Widgets/Images/SImage.h"
#include "Widgets/DeclarativeSyntaxSupport.h"

#define LOCTEXT_NAMESPACE "TaskActions"

void FTaskActions::OpenAssetEditor(const TArray<UObject*>& InObjects, TSharedPtr<class IToolkitHost> EditWithinLevelEditor /*= TSharedPtr<IToolkitHost>()*/)
{
	EToolkitMode::Type Mode = EditWithinLevelEditor.IsValid() ? EToolkitMode::WorldCentric : EToolkitMode::Standalone;
	for (auto ObjIt = InObjects.CreateConstIterator(); ObjIt; ++ObjIt)
	{
		auto CustomAsset = Cast<UTask>(*ObjIt);
		if (CustomAsset != nullptr)
		{
			TSharedRef<FTaskEditorToolkit> EditorToolKit = MakeShareable(new FTaskEditorToolkit());
			EditorToolKit->Initialize(CustomAsset, Mode, EditWithinLevelEditor);
		}
	}
}

TSharedPtr<class SWidget> FTaskActions::GetThumbnailOverlay(const FAssetData& AssetData) const
{
	return SNew(SImage);
}

FText FTaskActions::GetName() const
{
	return LOCTEXT("AssetName", "Task");
}

UClass* FTaskActions::GetSupportedClass() const
{
	return UTask::StaticClass();
}

FColor FTaskActions::GetTypeColor() const
{
	return FColor::Emerald;
}

uint32 FTaskActions::GetCategories()
{
	return ContigencyCategory;
}
#undef LOCTEXT_NAMESPACE