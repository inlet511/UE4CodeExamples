#include "ContingencyPlanActions.h"
#include "ContingencyPlan.h"
#include "ContingencyPlanEditor.h"
#include "ContingencyPlanEditorStyle.h"
#include "TaskFactory.h"
#include "Widgets/DeclarativeSyntaxSupport.h"
#include "Widgets/Images/SImage.h"

#define LOCTEXT_NAMESPACE "ContingencyPlanActions"
//
//void FContingencyPlanActions::OpenAssetEditor(const TArray<UObject*>& InObjects, TSharedPtr<class IToolkitHost> EditWithinLevelEditor /*= TSharedPtr<IToolkitHost>()*/)
//{
//	EToolkitMode::Type Mode = EditWithinLevelEditor.IsValid() ? EToolkitMode::WorldCentric : EToolkitMode::Standalone;
//	for (auto ObjIt = InObjects.CreateConstIterator(); ObjIt; ++ObjIt)
//	{
//		auto CustomAsset = Cast<UContingencyPlan>(*ObjIt);
//		if (CustomAsset != nullptr)
//		{
//			TSharedRef<FTaskEditorToolkit> EditorToolKit = MakeShareable(new FTaskEditorToolkit());
//			EditorToolKit->Initialize(CustomAsset, Mode, EditWithinLevelEditor);
//		}
//	}
//}

TSharedPtr<class SWidget> FContingencyPlanActions::GetThumbnailOverlay(const FAssetData& AssetData) const
{
	auto IconStyle = FContingencyPlanEditorStyle::Get().GetBrush("ContingencyPlanEditor.TaskIcon");
	return SNew(SImage)
	.Image(IconStyle);
}

FText FContingencyPlanActions::GetName() const
{
	return FText::GetEmpty();
}

UClass* FContingencyPlanActions::GetSupportedClass() const
{
	return UContingencyPlan::StaticClass();
}

FColor FContingencyPlanActions::GetTypeColor() const
{
	return FColor::Purple;
}

uint32 FContingencyPlanActions::GetCategories()
{
	return ContingencyCategory;
}
#undef LOCTEXT_NAMESPACE