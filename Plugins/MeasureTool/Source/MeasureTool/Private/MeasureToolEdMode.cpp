// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.

#include "MeasureToolEdMode.h"
#include "MeasureToolEdModeToolkit.h"
#include "Toolkits/ToolkitManager.h"
#include "EditorModeManager.h"
#include "EditorViewportClient.h"
#include "Kismet/KismetSystemLibrary.h"
#include "PointRulerTool.h"



const FEditorModeID FMeasureToolEdMode::EM_MeasureToolEdModeId = TEXT("EM_MeasureToolEdMode");

FMeasureToolEdMode::FMeasureToolEdMode()
{

}

FMeasureToolEdMode::~FMeasureToolEdMode()
{

}

void FMeasureToolEdMode::Initialize()
{
	PointRuler = MakeShareable(new FPointRulerTool());
	ObjectRuler = MakeShareable(new FObjectRulerTool());

	CurrentMeasureMode = EMeasureTool::OBJECT_RULER_TOOL;
}

void FMeasureToolEdMode::Enter()
{
	FEdMode::Enter();

	if (!Toolkit.IsValid() && UsesToolkits())
	{
		Toolkit = MakeShareable(new FMeasureToolEdModeToolkit);
		Toolkit->Init(Owner->GetToolkitHost());
	}


	PointRuler->RefreshAllMeshComponents();
}

void FMeasureToolEdMode::Exit()
{
	if (Toolkit.IsValid())
	{
		FToolkitManager::Get().CloseToolkit(Toolkit.ToSharedRef());
		Toolkit.Reset();
	}

	FEdMode::Exit();
}

void FMeasureToolEdMode::Tick(FEditorViewportClient* ViewportClient, float DeltaTime)
{	
	FEdMode::Tick(ViewportClient, DeltaTime);
	switch (CurrentMeasureMode)
	{
	case EMeasureTool::POINT_RULER_TOOL:
		PointRuler->Tick(ViewportClient, DeltaTime);	
		break;
	case EMeasureTool::OBJECT_RULER_TOOL:

		break;
	default:
		break;
	}
	
}

void FMeasureToolEdMode::Render(const FSceneView* View, FViewport* Viewport, FPrimitiveDrawInterface* PDI)
{
	FEdMode::Render(View, Viewport, PDI);
	switch (CurrentMeasureMode)
	{
	case EMeasureTool::POINT_RULER_TOOL:
		PointRuler->DrawGizmos(View, Viewport, PDI);
		break;
	case EMeasureTool::OBJECT_RULER_TOOL:

		break;
	default:
		break;
	}

	//切换工具不影响测量线的显示
	PointRuler->RenderAllMeasures(View, Viewport, PDI);
	ObjectRuler->RenderAllMeasures(View, Viewport, PDI);
}


bool FMeasureToolEdMode::UsesToolkits() const
{
	return true;
}

void FMeasureToolEdMode::DrawHUD(FEditorViewportClient* ViewportClient, FViewport* Viewport, const FSceneView* View, FCanvas* Canvas)
{	
	FEdMode::DrawHUD(ViewportClient, Viewport, View, Canvas);

	//切换工具不影响文字的显示
	PointRuler->DrawText(ViewportClient, Viewport, View, Canvas);
	ObjectRuler->DrawText(ViewportClient, Viewport, View, Canvas);
}

bool FMeasureToolEdMode::HandleClick(FEditorViewportClient* InViewportClient, HHitProxy* HitProxy, const FViewportClick& Click)
{
	
	switch (CurrentMeasureMode)
	{
	case EMeasureTool::POINT_RULER_TOOL:
		return PointRuler->HandleClick(InViewportClient, HitProxy, Click);

	case EMeasureTool::OBJECT_RULER_TOOL:
		return FEdMode::HandleClick(InViewportClient, HitProxy, Click);

	default:
		return FEdMode::HandleClick(InViewportClient, HitProxy, Click);
	}
	
}

void FMeasureToolEdMode::SetCurrentMeasureMode(EMeasureTool InMeasureMode)
{
	CurrentMeasureMode = InMeasureMode;
}

EMeasureTool FMeasureToolEdMode::GetCurrentMeasureMode()
{
	return CurrentMeasureMode;
}



