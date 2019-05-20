// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.

#include "ContigencyPlanEditorCommands.h"

#define LOCTEXT_NAMESPACE "FContigencyPlanEditorModule"

void FContigencyPlanEditorCommands::RegisterCommands()
{
	UI_COMMAND(PluginAction, "ContigencyPlanEditor", "Execute ContigencyPlanEditor action", EUserInterfaceActionType::Button, FInputGesture());
}

#undef LOCTEXT_NAMESPACE
