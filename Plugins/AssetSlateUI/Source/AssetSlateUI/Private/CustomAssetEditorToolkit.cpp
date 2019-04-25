#include "CustomAssetEditorToolkit.h"

#include "Widgets/Docking/SDockTab.h"
#include "Widgets/Images/SImage.h"

#define LOCTEXT_NAMESPACE "CustomAssetEditor"

namespace CustomAssetEditor
{
static const FName AppId("CustomAssetEditorApp");
static const FName AssetEditorID("CustomAssetEd");
}	// namespace CustomAssetEditor

void FCustomAssetEditorToolkit::RegisterTabSpawners(const TSharedRef<FTabManager>& InTabManager)
{
	Super::RegisterTabSpawners(InTabManager);
	InTabManager->RegisterTabSpawner(CustomAssetEditor::AssetEditorID, FOnSpawnTab::CreateLambda([&](const FSpawnTabArgs& Args) {
										 return SNew(SDockTab)
										 [SNew(SImage)];
									 }));
}

void FCustomAssetEditorToolkit::UnregisterTabSpawners(const TSharedRef<FTabManager>& InTabManager)
{
	Super::UnregisterTabSpawners(InTabManager);
	InTabManager->UnregisterTabSpawner(CustomAssetEditor::AssetEditorID);
}

FName FCustomAssetEditorToolkit::GetToolkitFName() const
{
	return FName("CustomAssetEditor");
}

FText FCustomAssetEditorToolkit::GetBaseToolkitName() const
{
	return LOCTEXT("AppLabel", "Custom Asset Editor");
}

FString FCustomAssetEditorToolkit::GetWorldCentricTabPrefix() const
{
	return LOCTEXT("WorldCentricTabPrefix", "CustomAsset").ToString();
}

FLinearColor FCustomAssetEditorToolkit::GetWorldCentricTabColorScale(void) const
{
	return FLinearColor(0.3f, 0.2f, 0.5f, 0.5f);
}

void FCustomAssetEditorToolkit::Initialize(UCustomAsset* InTextAsset, const EToolkitMode::Type InMode, const TSharedPtr<IToolkitHost>& InToolkitHost)
{
	InCustomAsset = InTextAsset;
	const TSharedRef<FTabManager::FLayout> StandaloneCustomLayout = FTabManager::NewLayout("StandaloneCustomLayout_Layout")
																	->AddArea(
																	FTabManager::NewPrimaryArea()
																	->Split(
																	FTabManager::NewStack()
																	->AddTab(CustomAssetEditor::AssetEditorID, ETabState::OpenedTab)));
	InitAssetEditor(
	InMode,
	InToolkitHost,
	CustomAssetEditor::AppId,
	StandaloneCustomLayout,
	true,
	true,
	InTextAsset);

	RegenerateMenusAndToolbars();
}

#undef LOCTEXT_NAMESPACE