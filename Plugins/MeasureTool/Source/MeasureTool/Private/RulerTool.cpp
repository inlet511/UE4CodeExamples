// Fill out your copyright notice in the Description page of Project Settings.

#include "RulerTool.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"
#include "DrawDebugHelpers.h"
#include "SharedPointer.h"

// Sets default values
ARulerTool::ARulerTool()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ARulerTool::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ARulerTool::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	DrawRuler(Start, End, Text);

}

bool ARulerTool::ShouldTickIfViewportsOnly() const
{
	return true;
}

void ARulerTool::DrawRuler(FVector Start, FVector End, FString Text)
{
	auto World = GetWorld();
	FColor DebugColor(0, 255, 0, 255);
	FVector Extend(1.0f);
	DrawDebugBox(World, Start, Extend, DebugColor,false,0.2f);
	if (StartConfirmed)
	{	
		DrawDebugBox(World, End, Extend, DebugColor);
		DrawDebugLine(World, Start, End, DebugColor);
		//DrawDebugString(World, , Text, 0,DebugColor);
	}
}


