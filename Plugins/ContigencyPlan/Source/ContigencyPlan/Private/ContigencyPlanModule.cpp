// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.

#include "ContigencyPlanModule.h"

#define LOCTEXT_NAMESPACE "ContigencyPlanModule"

void FContigencyPlanModule::StartupModule()
{
	UE_LOG(LogTemp, Warning, TEXT("ContigencyPlan Module Start"));
}

void FContigencyPlanModule::ShutdownModule()
{
	UE_LOG(LogTemp, Warning, TEXT("ContigencyPlan Module End"));
}

IMPLEMENT_MODULE(FContigencyPlanModule, ContigencyPlanModule)

#undef LOCTEXT_NAMESPACE