// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.

#include "EditorPluginSchemaCommands.h"

#define LOCTEXT_NAMESPACE "FEditorPluginSchemaModule"

void FEditorPluginSchemaCommands::RegisterCommands()
{
	UI_COMMAND(PluginAction, "EditorPluginSchema", "Execute EditorPluginSchema action", EUserInterfaceActionType::Button, FInputGesture());
}

#undef LOCTEXT_NAMESPACE
