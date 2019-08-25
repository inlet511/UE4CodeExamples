// CopyRight Mr. Art Digital Technology 2019
// Tool to measure point to point distance.

// Fill out your copyright notice in the Description page of Project Settings.

#include "AnnotationTool.h"
#include "GameFramework/Actor.h"
#include "CommonStructures.h"
#include "Engine/Selection.h"
#include "Editor.h"
#include "CanvasTypes.h"



void FAnnotationTool::RenderAllAnnotations(const FSceneView* View, FViewport* Viewport, FPrimitiveDrawInterface* PDI)
{
	for (auto item : Annotations)
	{
		PDI->DrawLine(item->LineStartPos, item->ShowTextPos, FColor::Purple, 0, 0);
	}
}



void FAnnotationTool::DrawText(FEditorViewportClient* ViewportClient, FViewport* Viewport, const FSceneView* View, FCanvas* Canvas)
{
	UFont* RenderFont = GEngine->GetSmallFont();
	for (auto anno : Annotations)
	{
		if (Canvas&&Annotations.Num() != 0)
		{
			FVector2D PixelLocation;
			View->ScreenToPixel(View->WorldToScreen(anno->ShowTextPos), PixelLocation);
			Canvas->DrawShadowedText(
				PixelLocation.X,
				PixelLocation.Y,
				anno->AnnotationContent,
				RenderFont,
				FColor::Purple);
		}
	}
}

void FAnnotationTool::AddAnnotation(FText AnnotationContent)
{
	USelection* Selection = GEditor->GetSelectedActors();
	if (Selection->Num() != 1 || AnnotationContent.IsEmpty())
	{
		return;
	}
	else
	{
		UObject* TargetObject = Selection->GetSelectedObject(0);
		AActor* TargetActor = Cast<AActor>(TargetObject);


		if (TargetActor != nullptr)
		{
			UAnnotation* annotation = NewObject<UAnnotation>();
			FVector TargetOrigin;
			FVector TargetBoxExtent;

			TargetActor->GetActorBounds(false, TargetOrigin, TargetBoxExtent);

			annotation->LineStartPos = TargetOrigin;
			annotation->ShowTextPos = TargetOrigin + FVector(0, 0, TargetBoxExtent.Z + 10.0f);
			annotation->AnnotationContent = AnnotationContent;

			Annotations.Add(annotation);
		}
	}
}
