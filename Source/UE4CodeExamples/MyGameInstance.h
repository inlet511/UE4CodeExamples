// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "Engine/StreamableManager.h"
#include "MyGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class UE4CODEEXAMPLES_API UMyGameInstance : public UGameInstance {
    GENERATED_BODY()
private:
    FStreamableManager MyStreamableManager;

public:
    FStreamableManager& GetStreamableManager() { return MyStreamableManager; }
};
