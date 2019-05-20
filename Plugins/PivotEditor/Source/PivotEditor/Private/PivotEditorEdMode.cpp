// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.

#include "PivotEditorEdMode.h"
#include "PivotEditorEdModeToolkit.h"
#include "Toolkits/ToolkitManager.h"
#include "EditorModeManager.h"

const FEditorModeID FPivotEditorEdMode::EM_PivotEditorEdModeId = TEXT("EM_PivotEditorEdMode");

FPivotEditorEdMode::FPivotEditorEdMode()
{

}

FPivotEditorEdMode::~FPivotEditorEdMode()
{

}

void FPivotEditorEdMode::Enter()
{
	FEdMode::Enter();

	if (!Toolkit.IsValid() && UsesToolkits())
	{
		Toolkit = MakeShareable(new FPivotEditorEdModeToolkit);
		Toolkit->Init(Owner->GetToolkitHost());
	}
}

void FPivotEditorEdMode::Exit()
{
	if (Toolkit.IsValid())
	{
		FToolkitManager::Get().CloseToolkit(Toolkit.ToSharedRef());
		Toolkit.Reset();
	}

	// Call base Exit method to ensure proper cleanup
	FEdMode::Exit();
}

bool FPivotEditorEdMode::UsesToolkits() const
{
	return true;
}




