#include "TaskActions.h"
#include "ContingencyPlanEditor.h"
#include "ContingencyPlanEditorStyle.h"
#include "Task.h"
#include "TaskEditorToolkit.h"
#include "TaskFactory.h"
#include "Widgets/DeclarativeSyntaxSupport.h"
#include "Widgets/Images/SImage.h"

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
	auto IconStyle = FContingencyPlanEditorStyle::Get().GetBrush("ContingencyPlanEditor.TaskIcon");
	return SNew(SImage)
	.Image(IconStyle);
}

FText FTaskActions::GetName() const
{
	return FText::GetEmpty();
}

UClass* FTaskActions::GetSupportedClass() const
{
	return UTask::StaticClass();
}

FColor FTaskActions::GetTypeColor() const
{
	return FColor::Purple;
}

uint32 FTaskActions::GetCategories()
{
	return ContingencyCategory;
}
#undef LOCTEXT_NAMESPACE