// Fill out your copyright notice in the Description page of Project Settings.

#include "TaskFactory.h"

#include "Task.h"

UTaskFactory::UTaskFactory(const FObjectInitializer& ObjectInitializer) :
	Super(ObjectInitializer)
{
	bCreateNew = true;
	bEditAfterNew = true;
	SupportedClass = UTask::StaticClass();
}

UObject* UTaskFactory::FactoryCreateNew(UClass* InClass, UObject* InParent, FName InName, EObjectFlags Flags, UObject* Context, FFeedbackContext* Warn, FName CallingContext)
{
	UTask* NewTaskAsset = NewObject<UTask>(InParent, InClass, InName, Flags | RF_Transactional);
	return NewTaskAsset;
}
