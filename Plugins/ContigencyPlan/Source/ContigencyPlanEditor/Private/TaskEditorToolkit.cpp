#include "TaskEditorToolkit.h"
#include "DeclarativeSyntaxSupport.h"
#include "SDockTab.h"
#include "SImage.h"

#define LOCTEXT_NAMESPACE "TaskEditor"

namespace TaskEditor
{
	static const FName AppId("TaskEditorApp");
	static const FName EditorID("TaskEd");
}

void FTaskEditorToolkit::RegisterTabSpawners(const TSharedRef<FTabManager>& InTabManager)
{
	FAssetEditorToolkit::RegisterTabSpawners(InTabManager);
	InTabManager->RegisterTabSpawner(
		TaskEditor::EditorID,
		FOnSpawnTab::CreateLambda([&](const FSpawnTabArgs& Args)
	{
		return SNew(SDockTab)
			[
				SNew(SImage)
			];
	})
	);
}

void FTaskEditorToolkit::UnregisterTabSpawners(const TSharedRef<FTabManager>& InTabManager)
{
	FAssetEditorToolkit::UnregisterTabSpawners(InTabManager);
	InTabManager->UnregisterTabSpawner(TaskEditor::EditorID);
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

void FTaskEditorToolkit::Initialize(UTask* InTaskAsset, const EToolkitMode::Type InMode, const TSharedPtr<IToolkitHost>& InToolkitHost)
{
	const TSharedRef<FTabManager::FLayout> StandaloneCustomLayout =
		FTabManager::NewLayout("StandaloneTaskLayout_Layout")
		->AddArea
		(
			FTabManager::NewPrimaryArea()
			->Split
			(
				FTabManager::NewStack()
				->AddTab(TaskEditor::EditorID, ETabState::OpenedTab)
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