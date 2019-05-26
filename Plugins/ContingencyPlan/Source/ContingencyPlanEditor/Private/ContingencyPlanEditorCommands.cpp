// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.

#include "ContingencyPlanEditorCommands.h"

#define LOCTEXT_NAMESPACE "FContingencyPlanEditorModule"

void FContingencyPlanEditorCommands::RegisterCommands()
{
	UI_COMMAND(PluginAction, "ContingencyPlanEditor", "Execute ContingencyPlanEditor action", EUserInterfaceActionType::Button, FInputGesture());
}

#undef LOCTEXT_NAMESPACE
