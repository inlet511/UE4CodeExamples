// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.

#include "MeasureToolEdMode.h"
#include "MeasureToolEdModeToolkit.h"
#include "Toolkits/ToolkitManager.h"
#include "EditorModeManager.h"
#include "EditorViewportClient.h"
#include "Kismet/KismetSystemLibrary.h"
#include "DrawDebugHelpers.h"

const FEditorModeID FMeasureToolEdMode::EM_MeasureToolEdModeId = TEXT("EM_MeasureToolEdMode");

FMeasureToolEdMode::FMeasureToolEdMode()
{

}

FMeasureToolEdMode::~FMeasureToolEdMode()
{

}

void FMeasureToolEdMode::Enter()
{
	FEdMode::Enter();
	UE_LOG(LogTemp, Warning, TEXT("Enter Measure Tool Mode"));

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
	UE_LOG(LogTemp, Warning, TEXT("Mode Tick"));
}

void FMeasureToolEdMode::Render(const FSceneView* View, FViewport* Viewport, FPrimitiveDrawInterface* PDI)
{
	
}

bool FMeasureToolEdMode::CapturedMouseMove(FEditorViewportClient* InViewportClient, FViewport* InViewport, int32 InMouseX, int32 InMouseY)
{
	UE_LOG(LogTemp, Warning, TEXT("Mode Render"));
	checkf(View && Viewport && PDI, TEXT("Invalid Viewport data"));
	FEditorViewportClient* ViewportClient = (FEditorViewportClient*)InViewport->GetClient();
	checkf(ViewportClient != nullptr, TEXT("Unable to retrieve viewport client"));

	if (ViewportClient->IsPerspective())
	{
		if (InViewport->IsCursorVisible())
		{

				// Grab the mouse cursor position
				FIntPoint MousePosition;
				InViewport->GetMousePos(MousePosition);

				// Is the mouse currently over the viewport? or flood filling
				if ((MousePosition.X >= 0 && MousePosition.Y >= 0 && MousePosition.X < (int32)Viewport->GetSizeXY().X && MousePosition.Y < (int32)Viewport->GetSizeXY().Y))
				{
					// Compute a world space ray from the screen space mouse coordinates
					FViewportCursorLocation MouseViewportRay(View, ViewportClient, MousePosition.X, MousePosition.Y);


					FVector CameraLocation = View->ViewMatrices.GetViewOrigin();
					FVector RayStart = MouseViewportRay.GetOrigin();
					FVector RayDirection = MouseViewportRay.GetDirection();
					FVector RayEnd = RayStart + RayDirection * 10000.0f;
					FCollisionQueryParams TraceParams;
					TraceParams.bTraceComplex = true;
					FHitResult HitResult;
					bool bHit = UKismetSystemLibrary::SphereTraceMulti(GetWorld(), RayStart, RayEnd, 30.0f, ECC_Visibility, true, nullptr, EDrawDebugTrace::ForDuration, HitResult, true, FLinearColor::Red, FLinearColor::Green, 2.0f);
					if (bHit)
					{
						DrawDebugBox(GetWorld(), HitResult.ImpactPoint, FVector(5.0f), FQuat::Identity, FColor::Purple);
					}

				}
			
		}
	}
}

bool FMeasureToolEdMode::UsesToolkits() const
{
	return true;
}




