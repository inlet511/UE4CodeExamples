// CopyRight Mr. Art Digital Technology 2019
// Tool to measure point to point distance.

#pragma once

#include "CoreMinimal.h"
#include "CommonStructures.h"

class FSceneView;
class FViewport;
class FPrimitiveDrawInterface;
class FEditorViewportClient;
class FCanvas;
class UStaticMeshComponent;
struct FViewportClick;

class FObjectRulerTool
{
public:

	void RenderAllMeasures(const FSceneView* View, FViewport* Viewport, FPrimitiveDrawInterface* PDI);
	void DrawText(FEditorViewportClient* ViewportClient, FViewport* Viewport, const FSceneView* View, FCanvas* Canvas);
	void AddMeasure();

private:
	//Measures
	TArray<UMeasure*> Measures;
};