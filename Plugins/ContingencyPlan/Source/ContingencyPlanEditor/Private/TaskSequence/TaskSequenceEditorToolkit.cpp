#include "TaskSequenceEditorToolkit.h"
#include "Widgets/Docking/SDockTab.h"
#include "Widgets/Images/SImage.h"
#include "Widgets/Layout/SScrollBox.h"
#include "TaskSequenceEditorSlate.h"

#define LOCTEXT_NAMESPACE "TaskSequenceEditor"

namespace TaskSequenceEditor
{
	static const FName AppId("TaskSequenceEditorApp");
	static const FName MainInfoID("MainPanel");
}

void FTaskSequenceEditorToolkit::RegisterTabSpawners(const TSharedRef<FTabManager>& InTabManager)
{
	FAssetEditorToolkit::RegisterTabSpawners(InTabManager);

	//×¢²áTab
	InTabManager->RegisterTabSpawner(
		TaskSequenceEditor::MainInfoID,
		FOnSpawnTab::CreateLambda([&](const FSpawnTabArgs& Args) {
		return SNew(SDockTab)
			[
				SNew(SScrollBox)
				+ SScrollBox::Slot()
				[
					SNew(STaskSequenceEditorSlate)
					.TaskSequence(EditingTaskSequence)
				]
			];
	}));
}

void FTaskSequenceEditorToolkit::UnregisterTabSpawners(const TSharedRef<FTabManager>& InTabManager)
{
	FAssetEditorToolkit::UnregisterTabSpawners(InTabManager);
	InTabManager->UnregisterTabSpawner(TaskSequenceEditor::MainInfoID);
}

FName FTaskSequenceEditorToolkit::GetToolkitFName() const
{
	return FName("TaskSequenceEditor");
}

FText FTaskSequenceEditorToolkit::GetBaseToolkitName() const
{
	return LOCTEXT("AppLabel", "TaskSequence Editor");
}

FString FTaskSequenceEditorToolkit::GetWorldCentricTabPrefix() const
{
	return LOCTEXT("WorldCentricTabPrefix", "ttttaskSequence").ToString();
}

FLinearColor FTaskSequenceEditorToolkit::GetWorldCentricTabColorScale(void) const
{
	return FLinearColor();
}

void FTaskSequenceEditorToolkit::Initialize(UTaskSequence * InTaskSequenceAsset, const EToolkitMode::Type InMode, const TSharedPtr<IToolkitHost>& InToolkitHost)
{
	EditingTaskSequence = InTaskSequenceAsset;
	const TSharedRef<FTabManager::FLayout> StandaloneCustomLayout =
		FTabManager::NewLayout("StandaloneTaskLayout_Layout")
		->AddArea
		(
			FTabManager::NewPrimaryArea()
			->Split
			(
				FTabManager::NewStack()
				->AddTab(TaskSequenceEditor::MainInfoID, ETabState::OpenedTab)
			)
		);
	InitAssetEditor
	(
		InMode,
		InToolkitHost,
		TaskSequenceEditor::AppId,
		StandaloneCustomLayout,
		true,
		true,
		InTaskSequenceAsset
	);
	RegenerateMenusAndToolbars();
}

#undef LOCTEXT_NAMESPACE