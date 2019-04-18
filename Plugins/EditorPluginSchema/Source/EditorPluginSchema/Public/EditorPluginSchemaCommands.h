// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Framework/Commands/Commands.h"
#include "EditorPluginSchemaStyle.h"

class FEditorPluginSchemaCommands : public TCommands<FEditorPluginSchemaCommands>
{
public:

	FEditorPluginSchemaCommands()
		: TCommands<FEditorPluginSchemaCommands>(TEXT("EditorPluginSchema"), NSLOCTEXT("Contexts", "EditorPluginSchema", "EditorPluginSchema Plugin"), NAME_None, FEditorPluginSchemaStyle::GetStyleSetName())
	{
	}

	// TCommands<> interface
	virtual void RegisterCommands() override;

public:
	TSharedPtr< FUICommandInfo > PluginAction;
};
