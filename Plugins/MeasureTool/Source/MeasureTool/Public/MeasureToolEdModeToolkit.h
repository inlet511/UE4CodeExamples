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


public:

	//缓存当前EditorMode
	class FMeasureToolEdMode * MeasureEdMode;

	TSharedPtr<SEditableTextBox> AnnotationInput;
	FReply AddMeasure();
	FReply SetCurrentMeasureTool(EMeasureTool InMeasureTool);
	FReply AddAnnotation();

	//是否是当前的工具
	EVisibility IsCurrentTool(EMeasureTool InMeasureTool) const;

	//上方工具栏按钮的激活状态
	bool ToolButtonActive(EMeasureTool InMeasureTool) const;

	//是否选择了N个对象
	bool SelectedNActors(int32 n) const;
};
