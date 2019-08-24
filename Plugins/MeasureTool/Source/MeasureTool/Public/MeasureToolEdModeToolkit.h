// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Toolkits/BaseToolkit.h"
#include "CommonStructures.h"
#include "Widgets/Input/SEditableTextBox.h"
#include "Brushes/SlateColorBrush.h"

class FMeasureToolEdModeToolkit : public FModeToolkit
{
public:

	FMeasureToolEdModeToolkit();
	
	/** FModeToolkit interface */
	virtual void Init(const TSharedPtr<IToolkitHost>& InitToolkitHost) override;

	/** IToolkit interface */
	virtual FName GetToolkitFName() const override;
	virtual FText GetBaseToolkitName() const override;
	virtual class FEdMode* GetEditorMode() const override;
	virtual TSharedPtr<class SWidget> GetInlineContent() const override { return ToolkitWidget; }	



private:

	TSharedPtr<SWidget> ToolkitWidget;


	FSlateColorBrush brush1 = FSlateColorBrush(FLinearColor(0.14f,0.06f,0.06f,1.0f));
	FSlateColorBrush brush2 = FSlateColorBrush(FLinearColor(0.06f, 0.12f, 0.14f, 1.0f));
	FSlateColorBrush brush3 = FSlateColorBrush(FLinearColor(0.06f, 0.14f, 0.07f, 1.0f));
	FSlateColorBrush brush4 = FSlateColorBrush(FLinearColor(1.0f, 1.0f, 1.0f, 1.0f));

public:

	//缓存当前EditorMode
	class FMeasureToolEdMode * MeasureEdMode;

	TSharedPtr<SEditableTextBox> AnnotationInput;
	FReply AddMeasure();
	FReply SetCurrentMeasureTool(EMeasureTool InMeasureTool);
	EVisibility IsCurrentTool(EMeasureTool InMeasureTool) const;
};
