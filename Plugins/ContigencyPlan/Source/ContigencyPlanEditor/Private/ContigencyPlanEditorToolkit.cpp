#include "ContigencyPlanEditorToolkit.h"

#define LOCTEXT_NAMESPACE "ContigencyPlanEditor"

void FContigencyPlanEditorToolkit::RegisterTabSpawners(const TSharedRef<FTabManager>& TabManager)
{

}

void FContigencyPlanEditorToolkit::UnregisterTabSpawners(const TSharedRef<FTabManager>& TabManager)
{
}

FName FContigencyPlanEditorToolkit::GetToolkitFName() const
{
	return FName("ContigencyPlanEditor");
}

FText FContigencyPlanEditorToolkit::GetBaseToolkitName() const
{
	return LOCTEXT("AppLabel", "Task Editor");
}

FString FContigencyPlanEditorToolkit::GetWorldCentricTabPrefix() const
{
	return LOCTEXT("WorldCentricTabPrefix", "ContigencyPlan").ToString();
}
#undef LOCTEXT_NAMESPACE