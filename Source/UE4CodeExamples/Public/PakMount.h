// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PakMount.generated.h"

UCLASS()
class UE4CODEEXAMPLES_API APakMount : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APakMount();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

    UFUNCTION(BlueprintCallable,Category="MountPak")
	void MountPak();
};
