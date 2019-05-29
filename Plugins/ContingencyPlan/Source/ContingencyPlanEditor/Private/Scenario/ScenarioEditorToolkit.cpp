#include "ScenarioEditorToolkit.h"

#define LOCTEXT_NAMESPACE "ScenarioEditor"

void FScenarioEditorToolkit::RegisterTabSpawners(const TSharedRef<FTabManager>& TabManager)
{
}

void FScenarioEditorToolkit::UnregisterTabSpawners(const TSharedRef<FTabManager>& TabManager)
{
}

FName FScenarioEditorToolkit::GetToolkitFName() const
{
	return FName("ScenarioEditor");
}

FText FScenarioEditorToolkit::GetBaseToolkitName() const
{
	return LOCTEXT("AppLabel", "Scenario Editor");
}

FString FScenarioEditorToolkit::GetWorldCentricTabPrefix() const
{
	return LOCTEXT("WorldCentricTabPrefix", "Scenario").ToString();
}

#undef LOCTEXT_NAMESPACE