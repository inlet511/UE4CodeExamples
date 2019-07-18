// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/TextRenderComponent.h"
#include "Components/StaticMeshComponent.h"
#include "EditorViewportClient.h"

class MEASURETOOL_API RulerTool
{
	
public:	
	// Sets default values for this actor's properties
	RulerTool();
	virtual ~RulerTool();


public:	
	static RulerTool* Get();
	virtual void Render(const FSceneView* View, FViewport* Viewport, FPrimitiveDrawInterface* PDI) ;
	// Called every frame
	virtual void Tick(FEditorViewportClient* ViewportClient, float DeltaTime) ;
	void ShowAllActors();

};
