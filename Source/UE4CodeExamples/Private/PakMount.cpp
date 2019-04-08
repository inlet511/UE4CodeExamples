// Fill out your copyright notice in the Description page of Project Settings.

#include "PakMount.h"

#include "HAL/PlatformFilemanager.h"
#include "IPlatformFilePak.h"
// Sets default values
APakMount::APakMount()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void APakMount::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void APakMount::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void APakMount::MountPak()
{
	IPlatformFile& InnerPlatform = FPlatformFileManager::Get().GetPlatformFile();
	FPakPlatformFile* PakPlatformFile = new FPakPlatformFile();
	PakPlatformFile->Initialize(&InnerPlatform, TEXT(""));
	FPlatformFileManager::Get().SetPlatformFile(*PakPlatformFile);


	bool bResult = PakPlatformFile->Mount(*FString(TEXT("D:\\ExamplePak.pak")), 0, *FPaths::GameContentDir());

	if (bResult)
	{
		GEngine->AddOnScreenDebugMessage(-1, 50.f, FColor::Red, FString::Printf(TEXT("EngineContentDir '%s'"), *FPaths::ProjectContentDir()));
	}
}