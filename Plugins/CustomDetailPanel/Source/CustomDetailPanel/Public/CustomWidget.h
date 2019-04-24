#pragma once

#include "SCompoundWidget.h"
#include "Widgets/DeclarativeSyntaxSupport.h"


class CUSTOMDETAILPANEL_API SCustomWidget : public SCompoundWidget
{
public:
	SLATE_BEGIN_ARGS(SCustomWidget){}
	//声明一个构造UI时可以传入的属性
	SLATE_ATTRIBUTE(class UCustomObject*, CustomObject)	
	
	SLATE_END_ARGS()

	void Construct(const FArguments& InArgs);

	TSharedPtr<class IDetailsView> ConfigPanel;

	//临时存储CustomObject属性
	TAttribute<class UCustomObject*> CustomObject;

};