// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.

#include "MeasureTool.h"
#include "MeasureToolEdMode.h"

#define LOCTEXT_NAMESPACE "FMeasureToolModule"

void FMeasureToolModule::StartupModule()
{
	// This code will execute after your module is loaded into memory; the exact timing is specified in the .uplugin file per-module
	FEditorModeRegistry::Get().RegisterMode<FMeasureToolEdMode>(FMeasureToolEdMode::EM_MeasureToolEdModeId, LOCTEXT("MeasureToolEdModeName", "MeasureToolEdMode"), FSlateIcon(), true);
}

void FMeasureToolModule::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.
	FEditorModeRegistry::Get().UnregisterMode(FMeasureToolEdMode::EM_MeasureToolEdModeId);
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FMeasureToolModule, MeasureTool)