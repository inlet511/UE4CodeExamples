// Fill out your copyright notice in the Description page of Project Settings.

#include "TaskSequenceFactory.h"

#include "TaskSequence.h"

UTaskSequenceFactory::UTaskSequenceFactory(const FObjectInitializer& ObjectInitializer) :
	Super(ObjectInitializer)
{
	bCreateNew = true;
	bEditAfterNew = true;
	SupportedClass = UTaskSequence::StaticClass();
}

UObject* UTaskSequenceFactory::FactoryCreateNew(UClass* InClass, UObject* InParent, FName InName, EObjectFlags Flags, UObject* Context, FFeedbackContext* Warn, FName CallingContext)
{
	UTaskSequence* NewTaskAsset = NewObject<UTaskSequence>(InParent, InClass, InName, Flags | RF_Transactional);
	return NewTaskAsset;
}
