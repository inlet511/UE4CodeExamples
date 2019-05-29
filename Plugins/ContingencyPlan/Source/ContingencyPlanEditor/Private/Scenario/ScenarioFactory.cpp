// Fill out your copyright notice in the Description page of Project Settings.

#include "ScenarioFactory.h"

#include "Scenario.h"

UScenarioFactory::UScenarioFactory(const FObjectInitializer& ObjectInitializer) :
	Super(ObjectInitializer)
{
	bCreateNew = true;
	bEditAfterNew = true;
	SupportedClass = UScenario::StaticClass();
}

UObject* UScenarioFactory::FactoryCreateNew(UClass* InClass, UObject* InParent, FName InName, EObjectFlags Flags, UObject* Context, FFeedbackContext* Warn, FName CallingContext)
{
	UScenario* NewTaskAsset = NewObject<UScenario>(InParent, InClass, InName, Flags | RF_Transactional);
	return NewTaskAsset;
}
