// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.

#include "ContingencyPlanModule.h"

#define LOCTEXT_NAMESPACE "ContingencyPlanModule"

void FContingencyPlanModule::StartupModule()
{
	UE_LOG(LogTemp, Warning, TEXT("ContingencyPlan Module Start"));
}

void FContingencyPlanModule::ShutdownModule()
{
	UE_LOG(LogTemp, Warning, TEXT("ContingencyPlan Module End"));
}

IMPLEMENT_MODULE(FContingencyPlanModule, ContingencyPlanModule)

#undef LOCTEXT_NAMESPACE