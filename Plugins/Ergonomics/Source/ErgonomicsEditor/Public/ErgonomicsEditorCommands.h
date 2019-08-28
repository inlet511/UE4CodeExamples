// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Framework/Commands/Commands.h"
#include "ErgonomicsEditorStyle.h"

class FErgonomicsEditorCommands : public TCommands<FErgonomicsEditorCommands>
{
public:
	FErgonomicsEditorCommands() :
		TCommands<FErgonomicsEditorCommands>(TEXT("Ergonomics"), NSLOCTEXT("Contexts", "Ergonomics", "Ergonomics Plugin"), NAME_None, FErgonomicsEditorStyle::GetStyleSetName())
	{
	}

	// TCommands<> interface
	virtual void RegisterCommands() override;

public:
	TSharedPtr<FUICommandInfo> OpenNIOSHWindow;
	TSharedPtr<FUICommandInfo> OpenREBAWindow;
	TSharedPtr<FUICommandInfo> OpenRULAWindow;
	TSharedPtr<FUICommandInfo> OpenWISHAWindow;
	TSharedPtr<FUICommandInfo> OpenSnookWindow;

};