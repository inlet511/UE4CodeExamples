// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.

#include "MeasureToolEdMode.h"
#include "MeasureToolEdModeToolkit.h"
#include "Toolkits/ToolkitManager.h"
#include "EditorModeManager.h"
#include "EditorViewportClient.h"
#include "Kismet/KismetSystemLibrary.h"
#include "DrawDebugHelpers.h"
#include "RulerTool.h"

const FEditorModeID FMeasureToolEdMode::EM_MeasureToolEdModeId = TEXT("EM_MeasureToolEdMode");

FMeasureToolEdMode::FMeasureToolEdMode()
{

}

FMeasureToolEdMode::~FMeasureToolEdMode()
{

}

void FMeasureToolEdMode::Initialize()
{
	Ruler = RulerTool::Get();
}

void FMeasureToolEdMode::Enter()
{
	FEdMode::Enter();
	UE_LOG(LogTemp, Warning, TEXT("Enter Measure Tool Mode"));

	Ruler->ShowAllActors();

	if (!Toolkit.IsValid() && UsesToolkits())
	{
		Toolkit = MakeShareable(new FMeasureToolEdModeToolkit);
		Toolkit->Init(Owner->GetToolkitHost());
	}
}

void FMeasureToolEdMode::Exit()
{
	if (Toolkit.IsValid())
	{
		FToolkitManager::Get().CloseToolkit(Toolkit.ToSharedRef());
		Toolkit.Reset();
	}
	UE_LOG(LogTemp, Warning, TEXT("Exit MesureTool Mode"));

	// Call base Exit method to ensure proper cleanup
	FEdMode::Exit();
}

void FMeasureToolEdMode::Tick(FEditorViewportClient* ViewportClient, float DeltaTime)
{
	FEdMode::Tick(ViewportClient, DeltaTime);
	Ruler->Tick(ViewportClient, DeltaTime);
}

void FMeasureToolEdMode::Render(const FSceneView* View, FViewport* Viewport, FPrimitiveDrawInterface* PDI)
{
	FEdMode::Render(View, Viewport, PDI);
	Ruler->Render(View, Viewport, PDI);
}

bool FMeasureToolEdMode::CapturedMouseMove(FEditorViewportClient* InViewportClient, FViewport* InViewport, int32 InMouseX, int32 InMouseY)
{
	if (InViewportClient->IsPerspective())
	{
		UE_LOG(LogTemp, Warning, TEXT("Mouse Moved: %d,%d"),InViewport->GetMouseX(),InViewport->GetMouseY());
	}
	return true;
}

bool FMeasureToolEdMode::UsesToolkits() const
{
	return true;
}




