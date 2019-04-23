#pragma once

#include "SCompoundWidget.h"
#include "Widgets/DeclarativeSyntaxSupport.h"


class CUSTOMDETAILPANEL_API SCustomWidget : public SCompoundWidget
{
public:
	SLATE_BEGIN_ARGS(SCustomWidget){}

	SLATE_ATTRIBUTE(class UCustomObject*, CustomObject)	
	
	SLATE_END_ARGS()

	void Construct(const FArguments& InArgs);

	TSharedPtr<class IDetailsView> ConfigPanel;

	TAttribute<class UCustomObject*> CustomObject;

};