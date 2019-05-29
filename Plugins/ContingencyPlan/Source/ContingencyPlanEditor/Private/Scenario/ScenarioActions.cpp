#include "ScenarioActions.h"

#include "ContingencyPlanEditor.h"
#include "ContingencyPlanEditorStyle.h"
#include "Scenario.h"
#include "TaskFactory.h"
#include "ScenarioFactory.h"
#include "Widgets/DeclarativeSyntaxSupport.h"
#include "Widgets/Images/SImage.h"
#include "Text.h"

#define LOCTEXT_NAMESPACE "ScenarioActions"

//void FScenarioActions::OpenAssetEditor(const TArray<UObject*>& InObjects, TSharedPtr<class IToolkitHost> EditWithinLevelEditor /*= TSharedPtr<IToolkitHost>()*/)
//{
//	EToolkitMode::Type Mode = EditWithinLevelEditor.IsValid() ? EToolkitMode::WorldCentric : EToolkitMode::Standalone;
//	for (auto ObjIt = InObjects.CreateConstIterator(); ObjIt; ++ObjIt)
//	{
//		auto CustomAsset = Cast<UTask>(*ObjIt);
//		if (CustomAsset != nullptr)
//		{
//			TSharedRef<FTaskEditorToolkit> EditorToolKit = MakeShareable(new FTaskEditorToolkit());
//			EditorToolKit->Initialize(CustomAsset, Mode, EditWithinLevelEditor);
//		}
//	}
//}

TSharedPtr<class SWidget> FScenarioActions::GetThumbnailOverlay(const FAssetData& AssetData) const
{
	auto IconStyle = FContingencyPlanEditorStyle::Get().GetBrush("ContingencyPlanEditor.TaskIcon");
	return SNew(SImage)
	.Image(IconStyle);
}

FText FScenarioActions::GetName() const
{
	return FText::GetEmpty();
}

UClass* FScenarioActions::GetSupportedClass() const
{
	return UScenario::StaticClass();
}

FColor FScenarioActions::GetTypeColor() const
{
	return FColor::Purple;
}

uint32 FScenarioActions::GetCategories()
{
	return ContingencyCategory;
}
#undef LOCTEXT_NAMESPACE