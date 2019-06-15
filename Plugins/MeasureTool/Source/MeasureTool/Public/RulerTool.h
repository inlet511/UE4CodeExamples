// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/TextRenderComponent.h"
#include "Components/StaticMeshComponent.h"
#include "RulerTool.generated.h"

UCLASS(Blueprintable,BlueprintType)
class MEASURETOOL_API ARulerTool : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ARulerTool();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual bool ShouldTickIfViewportsOnly() const override;

	void DrawRuler();

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	FVector Start;
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	FVector End;
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	UTextRenderComponent TextComp;
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	bool StartConfirmed = false;
};
