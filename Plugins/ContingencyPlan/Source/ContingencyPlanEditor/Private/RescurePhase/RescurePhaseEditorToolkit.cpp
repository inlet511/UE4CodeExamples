#include "RescurePhaseEditorToolkit.h"

#define LOCTEXT_NAMESPACE "RescurePhaseEditor"
void FRescurePhaseToolkit::RegisterTabSpawners(const TSharedRef<FTabManager>& TabManager)
{

}

void FRescurePhaseToolkit::UnregisterTabSpawners(const TSharedRef<FTabManager>& TabManager)
{

}

FName FRescurePhaseToolkit::GetToolkitFName() const
{
	return FName("RescurePhaseEditor");
}

FText FRescurePhaseToolkit::GetBaseToolkitName() const
{
	return LOCTEXT("AppLabel", "RescurePhase Editor");
}

FString FRescurePhaseToolkit::GetWorldCentricTabPrefix() const
{
	return LOCTEXT("WorldCentricTabPrefix", "RescurePhase").ToString();
}
#undef LOCTEXT_NAMESPACE