#include "ContingencyPlanEditorToolkit.h"

#define LOCTEXT_NAMESPACE "ContingencyPlanEditor"

void FContingencyPlanEditorToolkit::RegisterTabSpawners(const TSharedRef<FTabManager>& TabManager)
{

}

void FContingencyPlanEditorToolkit::UnregisterTabSpawners(const TSharedRef<FTabManager>& TabManager)
{
}

FName FContingencyPlanEditorToolkit::GetToolkitFName() const
{
	return FName("ContingencyPlanEditor");
}

FText FContingencyPlanEditorToolkit::GetBaseToolkitName() const
{
	return LOCTEXT("AppLabel", "Task Editor");
}

FString FContingencyPlanEditorToolkit::GetWorldCentricTabPrefix() const
{
	return LOCTEXT("WorldCentricTabPrefix", "ContingencyPlan").ToString();
}
#undef LOCTEXT_NAMESPACE