#pragma once
#include "EditorViewportClient.h"
#include "CustomAsset.h"
#include "PreviewScene.h"

class UProceduralMeshComponent;

class FCustomViewportClient : public FEditorViewportClient
{
public:
	FCustomViewportClient(const TWeakPtr<class SEditorViewport> &InEditorViewportWidget = nullptr);
	virtual void Tick(float DeltaSeconds) override;

	void SetCustomAsset(UCustomAsset* NewCustomAsset)
	{
		CustomAsset = NewCustomAsset;
	}

private:
	FPreviewScene DrawScene;
	UCustomAsset* CustomAsset;
	UProceduralMeshComponent* ProceduralMeshComponent;
};