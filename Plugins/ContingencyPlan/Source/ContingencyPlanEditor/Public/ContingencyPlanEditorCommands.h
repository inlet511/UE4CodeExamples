// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Framework/Commands/Commands.h"
#include "ContingencyPlanEditorStyle.h"

class FContingencyPlanEditorCommands : public TCommands<FContingencyPlanEditorCommands>
{
public:

	FContingencyPlanEditorCommands()
		: TCommands<FContingencyPlanEditorCommands>(TEXT("ContingencyPlanEditor"), NSLOCTEXT("Contexts", "ContingencyPlanEditor", "ContingencyPlanEditor Plugin"), NAME_None, FContingencyPlanEditorStyle::GetStyleSetName())
	{
	}

	// TCommands<> interface
	virtual void RegisterCommands() override;

public:
	TSharedPtr< FUICommandInfo > PluginAction;
};
