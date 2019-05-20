#include "FCustomViewportClient.h"

#include "AssetEditorModeManager.h"
#include "ProceduralMeshComponent.h"

FCustomViewportClient::FCustomViewportClient(const TWeakPtr<class SEditorViewport> &InEditorViewportWidget /*= nullptr*/) :
	FEditorViewportClient(NULL, &DrawScene, InEditorViewportWidget)
{
	PreviewScene = &DrawScene;
	((FAssetEditorModeManager *) ModeTools)->SetPreviewScene(PreviewScene);
	DrawHelper.bDrawGrid = true;
	DrawHelper.bDrawPivot = true;
	SetRealtime(true);
	ProceduralMeshComponent = NewObject<UProceduralMeshComponent>(PreviewScene->GetWorld(), TEXT("PreviewMesh"));
	PreviewScene->AddComponent(ProceduralMeshComponent, FTransform::Identity);
}

void FCustomViewportClient::Tick(float DeltaSeconds)
{
	FEditorViewportClient::Tick(DeltaSeconds);
	DrawScene.GetWorld()->Tick(LEVELTICK_All, DeltaSeconds);
}
