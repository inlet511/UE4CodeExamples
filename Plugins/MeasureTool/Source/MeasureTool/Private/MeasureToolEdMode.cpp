// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.

#include "MeasureToolEdMode.h"
#include "MeasureToolEdModeToolkit.h"
#include "Toolkits/ToolkitManager.h"
#include "EditorModeManager.h"

const FEditorModeID FMeasureToolEdMode::EM_MeasureToolEdModeId = TEXT("EM_MeasureToolEdMode");

FMeasureToolEdMode::FMeasureToolEdMode()
{

}

FMeasureToolEdMode::~FMeasureToolEdMode()
{

}

void FMeasureToolEdMode::Enter()
{
	FEdMode::Enter();

	if (!Toolkit.IsValid() && UsesToolkits())
	{
		Toolkit = MakeShareable(new FMeasureToolEdModeToolkit);
		Toolkit->Init(Owner->GetToolkitHost());
	}
}

void FMeasureToolEdMode::Exit()
{
	if (Toolkit.IsValid())
	{
		FToolkitManager::Get().CloseToolkit(Toolkit.ToSharedRef());
		Toolkit.Reset();
	}

	// Call base Exit method to ensure proper cleanup
	FEdMode::Exit();
}

bool FMeasureToolEdMode::UsesToolkits() const
{
	return true;
}




