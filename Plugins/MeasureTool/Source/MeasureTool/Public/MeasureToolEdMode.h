// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "EdMode.h"
#include "RulerTool.h"

enum class EMeasureMode : uint8
{
	RULER,
	ANGLEMETER
};

class MEASURETOOL_API FMeasure
{
public:
	FVector StartLocation;
	FVector EndLocation;
	FName Name;

	void SetMeasureName(const FText& Text) { Name = FName(*Text.ToString()); }
	FText GetMeasureName() { return FText::FromName(Name); }

	FMeasure() :
		StartLocation(FVector(0)),
		EndLocation(FVector(0)),
		Name("")
	{	};

	FMeasure(FVector _StartLocation, FVector _EndLocation, FName _Name = ""):
		StartLocation(_StartLocation),
		EndLocation(_EndLocation),
		Name(_Name)
	{	};

	~FMeasure()
	{
		Name = "";
	};
};



class FMeasureToolEdMode : public FEdMode
{
	struct FPaintRay
	{
		FVector CameraLocation;
		FVector RayStart;
		FVector RayDirection;
	};

public:
	const static FEditorModeID EM_MeasureToolEdModeId;
public:
	FMeasureToolEdMode();
	virtual ~FMeasureToolEdMode();

	// FEdMode interface
	virtual void Initialize() override;
	virtual void Enter() override;
	virtual void Exit() override;
	virtual void Tick(FEditorViewportClient* ViewportClient, float DeltaTime) override;
	virtual void Render(const FSceneView* View, FViewport* Viewport, FPrimitiveDrawInterface* PDI) override;
	virtual bool CapturedMouseMove(FEditorViewportClient* InViewportClient, FViewport* InViewport, int32 InMouseX, int32 InMouseY) override;
	virtual bool HandleClick(FEditorViewportClient* InViewportClient, HHitProxy* HitProxy, const FViewportClick& Click) override;
	virtual bool UsesToolkits() const override;
	virtual void DrawHUD(FEditorViewportClient* ViewportClient, FViewport* Viewport, const FSceneView* View, FCanvas* Canvas) override;
	// End of FEdMode interface
	
	EMeasureMode CurrentMeasureMode = EMeasureMode::RULER;
	void RefreshAllMeshComponents();
	void RetrieveMouseRay(const FSceneView* View, FViewport* Viewport, FPrimitiveDrawInterface* PDI, TArray<FPaintRay>& OutPaintRays);
	void RenderAllMeasures(const FSceneView* View, FViewport* Viewport, FPrimitiveDrawInterface* PDI);

	RulerTool* Ruler;
	TArray< FMeasure> Measures;

private: 
	TArray<UStaticMeshComponent*> AllMeshComponents;
	bool bIsMeasuring = false;
	bool HitSuccess = false;
	FHitResult BestHit;
	FVector BestLocation;
};
