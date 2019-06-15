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

	//当前TaskSequence的DetailsView
	TSharedPtr<IDetailsView> DetailsView;

	//选中的任务的DetailsView
	TSharedPtr<IDetailsView> TaskDetailsView;

	//显示任务链条的容器
	TSharedPtr<class SVerticalBox> tasksContainer;

	TArray<UTask*> CurrentTasks;

private:
	//以数组形式获取任务链条
	TArray<UTask*> GetTaskChain(UTaskSequence* taskSequence);

	//刷新Slate的子元素
	void OnLeadingTaskChanged(const FPropertyChangedEvent& event);

	//刷新任务图标
	void RefreshTaskIcons(UTaskSequence* InTaskSequence);

	// 点击任务按钮的响应
	FReply OnTaskButtonClicked(int32 ClickedIndex);

};