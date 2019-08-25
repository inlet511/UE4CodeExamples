// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.

#include "ErgonomicsCommands.h"

#define LOCTEXT_NAMESPACE "FErgonomicsModule"

void FErgonomicsCommands::RegisterCommands()
{
	UI_COMMAND(OpenNIOSHWindow, "NIOSH", "Bring up NIOSH window", EUserInterfaceActionType::Button, FInputGesture());
	UI_COMMAND(OpenREBAWindow, "REBA", "Bring up REBA window", EUserInterfaceActionType::Button, FInputGesture());
	UI_COMMAND(OpenRULAWindow, "RULA", "Bring up RULA window", EUserInterfaceActionType::Button, FInputGesture());
	UI_COMMAND(OpenWISHAWindow, "WISHA", "Bring up WISHA window", EUserInterfaceActionType::Button, FInputGesture());
	UI_COMMAND(OpenSnookWindow, "Snook", "Bring up Snook window", EUserInterfaceActionType::Button, FInputGesture());
}

#undef LOCTEXT_NAMESPACE
