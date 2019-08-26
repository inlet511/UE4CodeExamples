// Fill out your copyright notice in the Description page of Project Settings.


#include "SRULAWidget.h"
#include "SlateOptMacros.h"
#include "Widgets/Input/SButton.h"

BEGIN_SLATE_FUNCTION_BUILD_OPTIMIZATION
void SRULAWidget::Construct(const FArguments& InArgs)
{

	ChildSlot
	[
		SNew(SButton)
	];

}
END_SLATE_FUNCTION_BUILD_OPTIMIZATION
