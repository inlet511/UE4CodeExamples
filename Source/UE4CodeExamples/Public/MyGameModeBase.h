// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "TestThread.h"
#include "RunableInterface.h"
#include "MyGameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class UE4CODEEXAMPLES_API AMyGameModeBase : public AGameModeBase
{
	GENERATED_BODY()
	
public:
	virtual void BeginPlay() override;

	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason);

	//���߳�
	void PrintFunc();
private:
	IRunableInterface * Interface;
	TestThread * NewThread;
};
