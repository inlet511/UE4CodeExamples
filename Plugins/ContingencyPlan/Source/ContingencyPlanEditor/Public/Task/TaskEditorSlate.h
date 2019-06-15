#pragma once

#include "CoreMinimal.h"
#include "Widgets/SCompoundWidget.h"
#include "IDetailsView.h"

class STaskEditorSlate : public SCompoundWidget
{
public:
	SLATE_BEGIN_ARGS(STaskEditorSlate){}
	SLATE_ATTRIBUTE(class UTask*,Task)
	SLATE_END_ARGS()

	void Construct(const FArguments& InArgs);

private:
	class UTask* Task;

	TSharedPtr<IDetailsView> DetailView;
};