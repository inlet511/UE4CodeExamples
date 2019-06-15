#include "TaskSequenceActions.h"
#include "ContingencyPlanEditor.h"
#include "ContingencyPlanEditorStyle.h"
#include "TaskSequence.h"
#include "TaskSequenceEditorToolkit.h"
#include "TaskSequenceFactory.h"
#include "Widgets/DeclarativeSyntaxSupport.h"
#include "Widgets/Images/SImage.h"
#include "TaskFactory.h"

#define LOCTEXT_NAMESPACE "TaskSequenceActions"

void FTaskSequenceActions::OpenAssetEditor(const TArray<UObject*>& InObjects, TSharedPtr<class IToolkitHost> EditWithinLevelEditor /*= TSharedPtr<IToolkitHost>()*/)
{
	EToolkitMode::Type Mode = EditWithinLevelEditor.IsValid() ? EToolkitMode::WorldCentric : EToolkitMode::Standalone;
	for (auto ObjIt = InObjects.CreateConstIterator(); ObjIt; ++ObjIt)
	{
		auto CustomAsset = Cast<UTaskSequence>(*ObjIt);
		if (CustomAsset != nullptr)
		{
			TSharedRef<FTaskSequenceEditorToolkit> EditorToolKit = MakeShareable(new FTaskSequenceEditorToolkit());
			EditorToolKit->Initialize(CustomAsset, Mode, EditWithinLevelEditor);
		}
	}
}

TSharedPtr<class SWidget> FTaskSequenceActions::GetThumbnailOverlay(const FAssetData& AssetData) const
{
	auto IconStyle = FContingencyPlanEditorStyle::Get().GetBrush("ContingencyPlanEditor.TaskIcon");
	return SNew(SImage)
	.Image(IconStyle);
}

FText FTaskSequenceActions::GetName() const
{
	return FText::GetEmpty();
}

UClass* FTaskSequenceActions::GetSupportedClass() const
{
	return UTaskSequence::StaticClass();
}

FColor FTaskSequenceActions::GetTypeColor() const
{
	return FColor::Purple;
}

uint32 FTaskSequenceActions::GetCategories()
{
	return ContingencyCategory;
}
#undef LOCTEXT_NAMESPACE