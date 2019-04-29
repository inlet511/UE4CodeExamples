#pragma once

#include "CoreMinimal.h"
#include "Widgets/SCompoundWidget.h"
#include "Widgets/DeclarativeSyntaxSupport.h"
#include "Components/Widget.h"


class SCheckBox;

class SMainSlate : public SCompoundWidget
{
public:
	SLATE_BEGIN_ARGS(SMainSlate) {}
	SLATE_END_ARGS()

	void Construct(const FArguments& InArgs);

	template<int32 Index>
	void OnValChanged(ECheckBoxState NewState)
	{
		if (CheckBoxArray.IsValidIndex(Index))
		{
			for (int32 i = 0; i < CheckBoxArray.Num(); ++i)
			{
				if (CheckBoxArray[i].IsValid())
				{
					if (Index == i)
					{
						CheckBoxArray[i]->SetIsChecked(ECheckBoxState::Checked);
					}
					else
					{
						CheckBoxArray[i]->SetIsChecked(ECheckBoxState::Unchecked);
					}
				}
			}
		}
	}
protected:
	TArray <TSharedPtr<SCheckBox>> CheckBoxArray;
};