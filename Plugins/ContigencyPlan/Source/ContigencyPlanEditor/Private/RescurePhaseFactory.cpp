// Fill out your copyright notice in the Description page of Project Settings.

#include "RescurePhaseFactory.h"
#include "RescurePhase.h"

URescurePhaseFactory::URescurePhaseFactory(const FObjectInitializer& ObjectInitializer) :
	Super(ObjectInitializer)
{
	bCreateNew = true;
	bEditAfterNew = true;
	SupportedClass = URescurePhase::StaticClass();
}

UObject* URescurePhaseFactory::FactoryCreateNew(UClass* InClass, UObject* InParent, FName InName, EObjectFlags Flags, UObject* Context, FFeedbackContext* Warn, FName CallingContext)
{
	URescurePhase* NewTaskAsset = NewObject<URescurePhase>(InParent, InClass, InName, Flags | RF_Transactional);
	return NewTaskAsset;
}
