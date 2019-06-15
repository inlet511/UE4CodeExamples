#pragma once

#include "CoreMinimal.h"
#include "Widgets/SCompoundWidget.h"
#include "IDetailsView.h"

class STaskSequenceEditorSlate : public SCompoundWidget
{
public:
	SLATE_BEGIN_ARGS(STaskSequenceEditorSlate){}
	SLATE_ATTRIBUTE(class UTaskSequence*,TaskSequence)
	SLATE_END_ARGS()

	void Construct(const FArguments& InArgs);

private:

	class UTaskSequence* TaskSequence;

	//��ǰTaskSequence��DetailsView
	TSharedPtr<IDetailsView> DetailsView;

	//ѡ�е������DetailsView
	TSharedPtr<IDetailsView> TaskDetailsView;

	//��ʾ��������������
	TSharedPtr<class SVerticalBox> tasksContainer;

	TArray<UTask*> CurrentTasks;

private:
	//��������ʽ��ȡ��������
	TArray<UTask*> GetTaskChain(UTaskSequence* taskSequence);

	//ˢ��Slate����Ԫ��
	void OnLeadingTaskChanged(const FPropertyChangedEvent& event);

	//ˢ������ͼ��
	void RefreshTaskIcons(UTaskSequence* InTaskSequence);

	// �������ť����Ӧ
	FReply OnTaskButtonClicked(int32 ClickedIndex);

};