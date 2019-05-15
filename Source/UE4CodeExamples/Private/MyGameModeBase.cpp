// Fill out your copyright notice in the Description page of Project Settings.

#include "MyGameModeBase.h"

void AMyGameModeBase::BeginPlay()
{
	IRunableInterface * Interface = new IRunableInterface();
	TestThread * NewThread = new TestThread();

	NewThread->MyTestDelegate.BindUObject(this, &AMyGameModeBase::PrintFunc);

	NewThread->CreateThread(Interface);
}

void AMyGameModeBase::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);

	delete NewThread;
	Interface = nullptr;
}

//主线程执行内容
void AMyGameModeBase::PrintFunc()
{
	UE_LOG(LogTemp, Log, TEXT("PrintFunc"));
}
