#include "TaskSequenceEditorToolkit.h"

#define LOCTEXT_NAMESPACE "TaskSequenceEditor"

void FTaskSequenceEditorToolkit::RegisterTabSpawners(const TSharedRef<FTabManager>& TabManager)
{
}

void FTaskSequenceEditorToolkit::UnregisterTabSpawners(const TSharedRef<FTabManager>& TabManager)
{
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
	return LOCTEXT("WorldCentricTabPrefix", "TaskSequence").ToString();
}

#undef LOCTEXT_NAMESPACE