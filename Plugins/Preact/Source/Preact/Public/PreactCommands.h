// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Framework/Commands/Commands.h"
#include "PreactStyle.h"

class FPreactCommands : public TCommands<FPreactCommands>
{
public:

	FPreactCommands()
		: TCommands<FPreactCommands>(TEXT("Preact"), NSLOCTEXT("Contexts", "Preact", "Preact Plugin"), NAME_None, FPreactStyle::GetStyleSetName())
	{
	}

	// TCommands<> interface
	virtual void RegisterCommands() override;

public:
	TSharedPtr< FUICommandInfo > OpenPluginWindow;
};