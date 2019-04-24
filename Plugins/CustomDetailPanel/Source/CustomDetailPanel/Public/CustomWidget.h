#pragma once

#include "SCompoundWidget.h"
#include "Widgets/DeclarativeSyntaxSupport.h"


class CUSTOMDETAILPANEL_API SCustomWidget : public SCompoundWidget
{
public:
	SLATE_BEGIN_ARGS(SCustomWidget){}
	//����һ������UIʱ���Դ��������
	SLATE_ATTRIBUTE(class UCustomObject*, CustomObject)	
	
	SLATE_END_ARGS()

	void Construct(const FArguments& InArgs);

	TSharedPtr<class IDetailsView> ConfigPanel;

	//��ʱ�洢CustomObject����
	TAttribute<class UCustomObject*> CustomObject;

};