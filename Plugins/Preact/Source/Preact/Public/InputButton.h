#pragma once

#include "CoreMinimal.h"
#include "Widgets/SCompoundWidget.h"
#include "Widgets/DeclarativeSyntaxSupport.h"

class SInputButton : public SCompoundWidget
{
public:
	SLATE_BEGIN_ARGS(SInputButton) {}
	SLATE_END_ARGS()

	void Construct(const FArguments& InArgs);
};