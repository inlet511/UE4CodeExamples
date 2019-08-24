// Fill out your copyright notice in the Description page of Project Settings.

#include "PointRulerTool.h"
#include "DrawDebugHelpers.h"
#include "SharedPointer.h"
#include "EngineUtils.h"
#include "CanvasTypes.h"
#include "Components/StaticMeshComponent.h"
#include "Editor.h"
#include "Engine/Engine.h"
#include "MeasureToolEdMode.h"



void FPointRulerTool::DrawGizmos(const FSceneView* View, FViewport* Viewport, FPrimitiveDrawInterface* PDI)
{
	checkf(PDI != nullptr, TEXT("PDI is Null!"));

	TArray<FMeasureRay> OutPaitRays;
	RetrieveMouseRay(View, Viewport, PDI, OutPaitRays);

	// Iterate all PaintRays(There might be multiple paintRays in VR)
	for (FMeasureRay& PaintRay : OutPaitRays)
	{
		BestHit.Time = 1.0f;
		HitSuccess = false;

		// Iterate all Static Mesh Components in Scene
		for (auto Comp : AllMeshComponents)
		{
			//Exclude components whose bounds doesn't intersect the mouse ray
			FBox Box = Comp->Bounds.GetBox();
			bool hit = FMath::LineBoxIntersection(Box, PaintRay.RayStart, PaintRay.RayStart + PaintRay.RayDirection*10000000.0f, PaintRay.RayDirection*10000000.0f, (PaintRay.RayDirection*10000000.0f).Reciprocal());
			if (!hit) continue;

			FHitResult OutHit;
			FCollisionQueryParams TraceParams;
			TraceParams.bTraceComplex = true;

			if (Comp->LineTraceComponent(OutHit, PaintRay.RayStart, PaintRay.RayStart + PaintRay.RayDirection * 100000.0f, TraceParams))
			{
				// Find a Nearest Hit
				if (OutHit.Time < BestHit.Time)
				{
					BestHit = OutHit;
					HitSuccess = true;
				}
			}
		}
		if (HitSuccess)
		{
			FVector BrushXAxis, BrushYAxis;
			BestHit.Normal.FindBestAxisVectors(BrushXAxis, BrushYAxis);
			// Draw Gizmo
			DrawCircle(PDI, BestHit.Location + BestHit.Normal*0.15f, BrushXAxis, BrushYAxis, FColor::Cyan, 20.0f, 40, false, -1.0f, ESceneDepthPriorityGroup::SDPG_World, 1.0f);

			UStaticMeshComponent* MeshComp = Cast<UStaticMeshComponent>(BestHit.Component);
			const uint32 VertexCount = MeshComp->GetStaticMesh()->RenderData->LODResources[0].GetNumVertices();
			TArray<FVector> PosArray;
			PosArray.SetNum(VertexCount);
			float NearestDistance = 99999999.0f;
			BestLocation = FVector(0);

			for (uint32 idx = 0; idx < VertexCount; ++idx)
			{
				FVector v = MeshComp->GetStaticMesh()->RenderData->LODResources[0].VertexBuffers.PositionVertexBuffer.VertexPosition(idx);
				PosArray[idx] = (BestHit.Component->GetComponentTransform()).TransformPosition(v);
				if (FVector::DistSquared(PosArray[idx], BestHit.Location) < NearestDistance)
				{
					NearestDistance = FVector::DistSquared(PosArray[idx], BestHit.Location);
					BestLocation = PosArray[idx];
				}
			}
			PDI->DrawPoint(BestLocation, FColor::Green, 10, 0);
		}
	}
}

void FPointRulerTool::RetrieveMouseRay(const FSceneView* View, FViewport* Viewport, FPrimitiveDrawInterface* PDI, TArray<FMeasureRay>& OutPaintRays)
{
	checkf(View && Viewport && PDI, TEXT("Invalid Viewport data"));
	FEditorViewportClient* ViewportClient = (FEditorViewportClient*)Viewport->GetClient();
	checkf(ViewportClient != nullptr, TEXT("Unable to retrieve viewport client"));

	if (ViewportClient->IsPerspective())
	{
		if (Viewport->IsCursorVisible())
		{
			FIntPoint MousePosition;
			Viewport->GetMousePos(MousePosition);

			if ((MousePosition.X >= 0 && MousePosition.Y >= 0 && MousePosition.X < (int32)Viewport->GetSizeXY().X && MousePosition.Y < (int32)Viewport->GetSizeXY().Y))
			{
				// Compute a world space ray from the screen space mouse coordinates
				FViewportCursorLocation MouseViewportRay(View, ViewportClient, MousePosition.X, MousePosition.Y);

				FMeasureRay& NewPaintRay = *new(OutPaintRays) FMeasureRay();
				NewPaintRay.CameraLocation = View->ViewMatrices.GetViewOrigin();
				NewPaintRay.RayStart = MouseViewportRay.GetOrigin();
				NewPaintRay.RayDirection = MouseViewportRay.GetDirection();
			}
		}
	}
}


void FPointRulerTool::RefreshAllMeshComponents()
{
	//Empty All MeshComponents
	AllMeshComponents.Empty();

	for (TActorIterator<AActor> Iter(GEditor->GetEditorWorldContext().World()); Iter; ++Iter)
	{
		//Only count UStaticMeshComponents
		TArray<UStaticMeshComponent*> MeshComps;
		Iter->GetComponents<UStaticMeshComponent>(MeshComps);
		for (auto MeshComp : MeshComps)
		{
			AllMeshComponents.Add(MeshComp);
		}
	}
}


void FPointRulerTool::RenderAllMeasures(const FSceneView* View, FViewport* Viewport, FPrimitiveDrawInterface* PDI)
{
	
	for (auto item : Measures)
	{
		PDI->DrawLine(item->StartLocation, item->EndLocation, FColor::Cyan, 0, 0);
	}
}

bool FPointRulerTool::HandleClick(FEditorViewportClient* InViewportClient, HHitProxy* HitProxy, const FViewportClick& Click)
{
	if (HitSuccess)
	{
		if (!bIsMeasuring)
		{
			UMeasure* temp = NewObject<UMeasure>();
			temp->SetStartLocation(BestLocation);
			temp->SetEndLocation(BestLocation);
			Measures.Add(temp);
			bIsMeasuring = true;
		}
		else
		{
			Measures[Measures.Num() - 1]->SetEndLocation(BestLocation);
			bIsMeasuring = false;
		}
		return true;
	}
	return false;
}

void FPointRulerTool::DrawText(FEditorViewportClient* ViewportClient, FViewport* Viewport, const FSceneView* View, FCanvas* Canvas)
{
	UFont* RenderFont = GEngine->GetSmallFont();
	for (auto Measure : Measures)
	{
		if (Canvas&&Measures.Num() != 0)
		{
			FVector TextPos = (Measure->StartLocation + Measure->EndLocation) * 0.5f;
			float distance = FVector::Distance(Measure->StartLocation, Measure->EndLocation);
			FString DrawString(FString::SanitizeFloat(distance) + TEXT(" cm"));
			FVector2D PixelLocation;
			View->ScreenToPixel(View->WorldToScreen(TextPos), PixelLocation);
			Canvas->DrawShadowedText(
				PixelLocation.X,
				PixelLocation.Y,
				FText::FromString(DrawString),
				RenderFont,
				FColor::Cyan);
		}
	}
}

// Called every frame
void FPointRulerTool::Tick(FEditorViewportClient* ViewportClient, float DeltaTime)
{



}

