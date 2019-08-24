// CopyRight Mr. Art Digital Technology 2019
// Tool to measure point to point distance.

#pragma once

#include "CoreMinimal.h"
#include "NoExportTypes.h"
#include "EditorViewportClient.h"
#include "CommonStructures.h"


class FSceneView;
class FViewport;
class FPrimitiveDrawInterface;
class FEditorViewportClient;
class FCanvas;
class UStaticMeshComponent;

class FPointRulerTool
{

public:

	void DrawGizmos(const FSceneView* View, FViewport* Viewport, FPrimitiveDrawInterface* PDI);
	void Tick(FEditorViewportClient* ViewportClient, float DeltaTime);
	void RetrieveMouseRay(const FSceneView* View, FViewport* Viewport, FPrimitiveDrawInterface* PDI, TArray<struct FMeasureRay>& OutPaintRays);
	void RefreshAllMeshComponents();
	void RenderAllMeasures(const FSceneView* View, FViewport* Viewport, FPrimitiveDrawInterface* PDI);
	bool HandleClick(FEditorViewportClient* InViewportClient, class HHitProxy* HitProxy, const FViewportClick& Click);
	void DrawText(FEditorViewportClient* ViewportClient, FViewport* Viewport, const FSceneView* View, FCanvas* Canvas);


private:

	
	TArray<UStaticMeshComponent*> AllMeshComponents;
	bool bIsMeasuring = false;
	bool HitSuccess = false;
	struct FHitResult BestHit;
	FVector BestLocation;

	//Measures
	TArray<UMeasure*> Measures;
};