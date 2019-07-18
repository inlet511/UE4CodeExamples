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


class FMeasureToolEdMode : public FEdMode
{
public:
	const static FEditorModeID EM_MeasureToolEdModeId;
public:
	FMeasureToolEdMode();
	virtual ~FMeasureToolEdMode();

	//当前使用尺子还是量角器
	EMeasureMode CurrentMeasureMode = EMeasureMode::RULER;

	// FEdMode interface
	virtual void Initialize() override;
	virtual void Enter() override;
	virtual void Exit() override;
	virtual void Tick(FEditorViewportClient* ViewportClient, float DeltaTime) override;
	virtual void Render(const FSceneView* View, FViewport* Viewport, FPrimitiveDrawInterface* PDI) override;
	//virtual void ActorSelectionChangeNotify() override;
	virtual bool CapturedMouseMove(FEditorViewportClient* InViewportClient, FViewport* InViewport, int32 InMouseX, int32 InMouseY) override;

	bool UsesToolkits() const override;
	// End of FEdMode interface

	RulerTool* Ruler;
};
