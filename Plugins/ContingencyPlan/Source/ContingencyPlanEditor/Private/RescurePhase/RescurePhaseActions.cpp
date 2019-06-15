#include "RescurePhaseActions.h"

#include "ContingencyPlanEditor.h"
#include "ContingencyPlanEditorStyle.h"
#include "RescurePhase.h"
#include "TaskFactory.h"
#include "RescurePhaseFactory.h"
#include "Widgets/DeclarativeSyntaxSupport.h"
#include "Widgets/Images/SImage.h"


#define LOCTEXT_NAMESPACE "RescurePhaseActions"

//void FRescurePhaseActions::OpenAssetEditor(const TArray<UObject*>& InObjects, TSharedPtr<class IToolkitHost> EditWithinLevelEditor /*= TSharedPtr<IToolkitHost>()*/)
//{
//	EToolkitMode::Type Mode = EditWithinLevelEditor.IsValid() ? EToolkitMode::WorldCentric : EToolkitMode::Standalone;
//	for (auto ObjIt = InObjects.CreateConstIterator(); ObjIt; ++ObjIt)
//	{
//		auto CustomAsset = Cast<URescurePhase>(*ObjIt);
//		if (CustomAsset != nullptr)
//		{
//			TSharedRef<FTaskEditorToolkit> EditorToolKit = MakeShareable(new FTaskEditorToolkit());
//			EditorToolKit->Initialize(CustomAsset, Mode, EditWithinLevelEditor);
//		}
//	}
//}

TSharedPtr<class SWidget> FRescurePhaseActions::GetThumbnailOverlay(const FAssetData& AssetData) const
{
	auto IconStyle = FContingencyPlanEditorStyle::Get().GetBrush("ContingencyPlanEditor.TaskIcon");
	return SNew(SImage)
	.Image(IconStyle);
}

FText FRescurePhaseActions::GetName() const
{
	return FText::GetEmpty();
}

UClass* FRescurePhaseActions::GetSupportedClass() const
{
	return URescurePhase::StaticClass();
}

FColor FRescurePhaseActions::GetTypeColor() const
{
	return FColor::Purple;
}

uint32 FRescurePhaseActions::GetCategories()
{
	return ContingencyCategory;
}
#undef LOCTEXT_NAMESPACE