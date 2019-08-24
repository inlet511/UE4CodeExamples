// Fill out your copyright notice in the Description page of Project Settings.

#include "ObjectRulerTool.h"
#include "GameFramework/Actor.h"
#include "CommonStructures.h"
#include "Engine/Selection.h"
#include "Editor.h"
#include "CanvasTypes.h"



void FObjectRulerTool::RenderAllMeasures(const FSceneView* View, FViewport* Viewport, FPrimitiveDrawInterface* PDI)
{
	for (auto item : Measures)
	{
		PDI->DrawLine(item->StartLocation, item->EndLocation, FColor::Orange, 0, 0);
	}
}



void FObjectRulerTool::DrawText(FEditorViewportClient* ViewportClient, FViewport* Viewport, const FSceneView* View, FCanvas* Canvas)
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
				FColor::Orange);
		}
	}
}

void FObjectRulerTool::AddMeasure()
{
	USelection* Selection = GEditor->GetSelectedActors();
	if (Selection->Num()!= 2)
	{
		return;
	}
	else
	{
		UObject* From = Selection->GetSelectedObject(0);
		UObject* To = Selection->GetSelectedObject(1);
		AActor* FromActor = Cast<AActor>(From);
		AActor* ToActor = Cast<AActor>(To);

		if (FromActor!= nullptr && 	ToActor != nullptr)
		{
			UMeasure* m = NewObject<UMeasure>();

			FVector FromOrigin;
			FVector FromBoxExtent;
			FVector ToOrigin;
			FVector ToBoxExtent;

			FromActor->GetActorBounds(false, FromOrigin, FromBoxExtent);
			ToActor->GetActorBounds(false, ToOrigin, ToBoxExtent);
			m->SetStartLocation(FromOrigin);
			m->SetEndLocation(ToOrigin);
			Measures.Add(m);
		}
	}	
}
