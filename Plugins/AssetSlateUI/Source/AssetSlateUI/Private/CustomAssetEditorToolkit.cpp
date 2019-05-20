#include "CustomAssetEditorToolkit.h"
#include "Widgets/Docking/SDockTab.h"
#include "Widgets/Images/SImage.h"
#include "SCustomViewport.h"

#define LOCTEXT_NAMESPACE "CustomAssetEditor"

namespace CustomAssetEditor
{
static const FName AppId("CustomAssetEditorApp");
static const FName AssetEditorID("CustomAssetEd");
}

void FCustomAssetEditorToolkit::RegisterTabSpawners(const TSharedRef<FTabManager>& InTabManager)
{
	Super::RegisterTabSpawners(InTabManager);
	InTabManager->RegisterTabSpawner(
		CustomAssetEditor::AssetEditorID, 
		FOnSpawnTab::CreateLambda([&](const FSpawnTabArgs& Args) 
		{
			return SNew(SDockTab)
				[
					SNew(SCustomViewport)
					.CustomAsset(InCustomAsset)
				];
		})
	);
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
	//创建Layout,添加一个主要区域，并对它进行划分，向内部加入一个Tab，并指定Tab的名称和类型
	const TSharedRef<FTabManager::FLayout> StandaloneCustomLayout = 
		FTabManager::NewLayout("StandaloneCustomLayout_Layout")
		->AddArea
		(
			FTabManager::NewPrimaryArea()
			->Split
			(
				FTabManager::NewStack()
				->AddTab(CustomAssetEditor::AssetEditorID, ETabState::OpenedTab)
			)
		);

	InCustomAsset = InTextAsset;

	InitAssetEditor
	(
		InMode,
		InToolkitHost,
		CustomAssetEditor::AppId,
		StandaloneCustomLayout,
		true,
		true,
		InTextAsset
	);

	RegenerateMenusAndToolbars();
}

#undef LOCTEXT_NAMESPACE