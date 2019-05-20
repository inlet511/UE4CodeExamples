// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Framework/Commands/Commands.h"
#include "ContigencyPlanEditorStyle.h"

class FContigencyPlanEditorCommands : public TCommands<FContigencyPlanEditorCommands>
{
public:

	FContigencyPlanEditorCommands()
		: TCommands<FContigencyPlanEditorCommands>(TEXT("ContigencyPlanEditor"), NSLOCTEXT("Contexts", "ContigencyPlanEditor", "ContigencyPlanEditor Plugin"), NAME_None, FContigencyPlanEditorStyle::GetStyleSetName())
	{
	}

	// TCommands<> interface
	virtual void RegisterCommands() override;

public:
	TSharedPtr< FUICommandInfo > PluginAction;
};
