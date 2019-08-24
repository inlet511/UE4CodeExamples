// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "EdMode.h"
#include "PointRulerTool.h"
#include "ObjectRulerTool.h"


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
	TSharedPtr<FPointRulerTool> PointRuler;
	TSharedPtr<FObjectRulerTool> ObjectRuler;

	void SetCurrentMeasureMode(EMeasureTool InMeasureMode);
	EMeasureTool GetCurrentMeasureMode();
};
