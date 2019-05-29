#include "TaskEditorToolkit.h"
#include "DeclarativeSyntaxSupport.h"
#include "SDockTab.h"
#include "SImage.h"
#include "Widgets/Layout/SScrollBox.h"
#include "TaskEditorSlate.h"

#define LOCTEXT_NAMESPACE "TaskEditor"

namespace TaskEditor
{
	static const FName AppId("TaskEditorApp");
	static const FName MainInfoID("MainPanel");
}

void FTaskEditorToolkit::RegisterTabSpawners(const TSharedRef<FTabManager>& InTabManager)
{
	FAssetEditorToolkit::RegisterTabSpawners(InTabManager);


	//×¢²áTab
	InTabManager->RegisterTabSpawner(
	TaskEditor::MainInfoID,
	FOnSpawnTab::CreateLambda([&](const FSpawnTabArgs& Args) {
		return SNew(SDockTab)
		[
			SNew(SScrollBox)
			+ SScrollBox::Slot()
			[
				SNew(STaskEditorSlate)
					.Task(EditingTask)
			]
		];
	}));
}

void FTaskEditorToolkit::UnregisterTabSpawners(const TSharedRef<FTabManager>& InTabManager)
{
	FAssetEditorToolkit::UnregisterTabSpawners(InTabManager);
	InTabManager->UnregisterTabSpawner(TaskEditor::MainInfoID);
}

FName FTaskEditorToolkit::GetToolkitFName() const
{
	return FName("TaskEditor");
}

FText FTaskEditorToolkit::GetBaseToolkitName() const
{
	return LOCTEXT("AppLabel", "Task Editor");
}

FString FTaskEditorToolkit::GetWorldCentricTabPrefix() const
{
	return LOCTEXT("WorldCentricTabPrefix", "TaskAsset").ToString();
}

FLinearColor FTaskEditorToolkit::GetWorldCentricTabColorScale(void) const
{
	return FLinearColor(0.3f, 0.2f, 0.5f, 0.5f);
}

void FTaskEditorToolkit::Initialize(
	UTask* InTaskAsset, 
	const EToolkitMode::Type InMode, 
	const TSharedPtr<IToolkitHost>& InToolkitHost)
{
	EditingTask = InTaskAsset;
	const TSharedRef<FTabManager::FLayout> StandaloneCustomLayout =
		FTabManager::NewLayout("StandaloneTaskLayout_Layout")
		->AddArea
		(
			FTabManager::NewPrimaryArea()
			->Split
			(
				FTabManager::NewStack()
				->AddTab(TaskEditor::MainInfoID, ETabState::OpenedTab)
			)
		);
	InitAssetEditor
	(
		InMode,
		InToolkitHost,
		TaskEditor::AppId,
		StandaloneCustomLayout,
		true,
		true,
		InTaskAsset
	);
	RegenerateMenusAndToolbars();
}

#undef LOCTEXT_NAMESPACE