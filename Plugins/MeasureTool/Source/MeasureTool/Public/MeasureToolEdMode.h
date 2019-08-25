// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "EdMode.h"
#include "CommonStructures.h"



class FMeasureToolEdMode : public FEdMode
{

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
	virtual bool UsesToolkits() const override;
	virtual void DrawHUD(FEditorViewportClient* ViewportClient, FViewport* Viewport, const FSceneView* View, FCanvas* Canvas) override;
	virtual bool HandleClick(FEditorViewportClient* InViewportClient, HHitProxy* HitProxy, const FViewportClick& Click) override;
	// End of FEdMode interface	



private: 
	enum EMeasureTool CurrentMeasureMode;

public:
	//SubTools
	TSharedPtr<class FPointRulerTool> PointRuler;
	TSharedPtr<class FObjectRulerTool> ObjectRuler;
	TSharedPtr<class FAnnotationTool> AnnotationTool;

	void SetCurrentMeasureMode(EMeasureTool InMeasureMode);
	EMeasureTool GetCurrentMeasureMode();
};
