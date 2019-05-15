// Fill out your copyright notice in the Description page of Project Settings.

#include "MyGameModeBase.h"

void AMyGameModeBase::BeginPlay()
{
	IRunableInterface * Interface = new IRunableInterface();
	TestThread * NewThread = new TestThread();
	NewThread->CreateThread(Interface);
}

void AMyGameModeBase::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);

	delete NewThread;
	Interface = nullptr;
}
