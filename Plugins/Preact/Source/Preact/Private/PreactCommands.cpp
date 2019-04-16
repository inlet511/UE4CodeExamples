// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.

#include "PreactCommands.h"

#define LOCTEXT_NAMESPACE "FPreactModule"

void FPreactCommands::RegisterCommands()
{
	UI_COMMAND(OpenPluginWindow, "Preact", "Bring up Preact window", EUserInterfaceActionType::Button, FInputGesture());
}

#undef LOCTEXT_NAMESPACE
