#include "TaskEditorToolkit.h"

#define LOCTEXT_NAMESPACE "TaskEditor"

//void FTaskEditorToolkit::RegisterTabSpawners(const TSharedRef<FTabManager>& TabManager)
//{
//}
//
//void FTaskEditorToolkit::UnregisterTabSpawners(const TSharedRef<FTabManager>& TabManager)
//{
//}

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

#undef LOCTEXT_NAMESPACE