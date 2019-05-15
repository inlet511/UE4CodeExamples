// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.

#include "MeasureToolEdModeToolkit.h"
#include "MeasureToolEdMode.h"
#include "Engine/Selection.h"
#include "Widgets/Input/SButton.h"
#include "Widgets/Text/STextBlock.h"
#include "EditorModeManager.h"

#define LOCTEXT_NAMESPACE "FMeasureToolEdModeToolkit"

FMeasureToolEdModeToolkit::FMeasureToolEdModeToolkit()
{
}

void FMeasureToolEdModeToolkit::Init(const TSharedPtr<IToolkitHost>& InitToolkitHost)
{
	struct Locals
	{
		static bool IsWidgetEnabled()
		{
			return GEditor->GetSelectedActors()->Num() != 0;
		}

		static FReply OnButtonClick(FVector InOffset)
		{
			USelection* SelectedActors = GEditor->GetSelectedActors();

			// Let editor know that we're about to do something that we want to undo/redo
			GEditor->BeginTransaction(LOCTEXT("MoveActorsTransactionName", "MoveActors"));

			// For each selected actor
			for (FSelectionIterator Iter(*SelectedActors); Iter; ++Iter)
			{
				if (AActor* LevelActor = Cast<AActor>(*Iter))
				{
					// Register actor in opened transaction (undo/redo)
					LevelActor->Modify();
					// Move actor to given location
					LevelActor->TeleportTo(LevelActor->GetActorLocation() + InOffset, FRotator(0, 0, 0));
				}
			}

			// We're done moving actors so close transaction
			GEditor->EndTransaction();

			return FReply::Handled();
		}
		static FReply OnRulerButtonClicked()
		{
			UE_LOG(LogTemp, Log, TEXT("RulerButtonClicked"));
			return FReply::Handled();
		}
		static FReply OnAngleButtonClicked()
		{
			UE_LOG(LogTemp, Log, TEXT("AngleButtonClicked"));
			return FReply::Handled();
		}

	};

	const float Factor = 256.0f;

	SAssignNew(ToolkitWidget, SBorder)
		.HAlign(HAlign_Center)

		//.IsEnabled_Static(&Locals::IsWidgetEnabled)
		[
			SNew(SVerticalBox)

			+ SVerticalBox::Slot()
				.HAlign(HAlign_Center)
				.AutoHeight()
				[
					SNew(SButton)
					.Text(LOCTEXT("RulerTool", "RulerTool"))
					.OnClicked_Static(&Locals::OnRulerButtonClicked)
				]
			+ SVerticalBox::Slot()
				.HAlign(HAlign_Center)
				.AutoHeight()
				[
					SNew(SButton)
					.Text(LOCTEXT("RulerTool", "RulerTool"))
					.OnClicked_Static(&Locals::OnAngleButtonClicked)
					
				]
			+ SVerticalBox::Slot()
				.HAlign(HAlign_Center)
				.AutoHeight()
				[
					SNew(SButton)
					.Text(LOCTEXT("DeleteTool", "DeleteTool"))
					.OnClicked_Static(&Locals::OnAngleButtonClicked)
				]

		];
		
	FModeToolkit::Init(InitToolkitHost);
}

FName FMeasureToolEdModeToolkit::GetToolkitFName() const
{
	return FName("MeasureToolEdMode");
}

FText FMeasureToolEdModeToolkit::GetBaseToolkitName() const
{
	return NSLOCTEXT("MeasureToolEdModeToolkit", "DisplayName", "MeasureToolEdMode Tool");
}

class FEdMode* FMeasureToolEdModeToolkit::GetEditorMode() const
{
	return GLevelEditorModeTools().GetActiveMode(FMeasureToolEdMode::EM_MeasureToolEdModeId);
}

#undef LOCTEXT_NAMESPACE
