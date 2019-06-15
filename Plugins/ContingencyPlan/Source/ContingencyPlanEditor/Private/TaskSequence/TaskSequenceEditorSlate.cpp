#include "TaskSequenceEditorSlate.h"
#include "Task.h"
#include "TaskSequence.h"
#include "Widgets/Layout/SBox.h"
#include "Widgets/Layout/SBorder.h"
#include "Widgets/SBoxPanel.h"
#include "Widgets/Images/SImage.h"
#include "Widgets/DeclarativeSyntaxSupport.h"
#include "Widgets/Text/STextBlock.h"
#include "Widgets/Input/SButton.h"
#include "Modules/ModuleManager.h"
#include "PropertyEditorModule.h"

#define LOCTEXT_NAMESPACE "TaskSequenceEditorSlate"

void STaskSequenceEditorSlate::Construct(const FArguments& InArgs)
{
	//从传入的参数中获取Task对象
	TaskSequence = InArgs._TaskSequence.Get();

	auto& PropertyModule = FModuleManager::LoadModuleChecked<FPropertyEditorModule>("PropertyEditor");

	//创建DetailView
	FDetailsViewArgs DetailsViewArgs; 
	DetailsViewArgs.bShowScrollBar = true;
	DetailsViewArgs.NameAreaSettings = FDetailsViewArgs::ENameAreaSettings::HideNameArea;
	DetailsView = PropertyModule.CreateDetailView(DetailsViewArgs);
	DetailsView->SetObject(TaskSequence,true);

	//创建TaskDetailsView
	FDetailsViewArgs TaskDetailsViewArgs;
	TaskDetailsViewArgs.bShowScrollBar = true;
	TaskDetailsViewArgs.NameAreaSettings = FDetailsViewArgs::ENameAreaSettings::HideNameArea;
	TaskDetailsView = PropertyModule.CreateDetailView(TaskDetailsViewArgs);
	

	//初始化任务容器
	tasksContainer = SNew(SVerticalBox);

	DetailsView->OnFinishedChangingProperties().AddSP(this, &STaskSequenceEditorSlate::OnLeadingTaskChanged);	

	//实现UI
	ChildSlot
		[
			SNew(SVerticalBox) 
			+ SVerticalBox::Slot()
			.AutoHeight()
			[
				SNew(SBox)
				.WidthOverride(300)
				.MinDesiredWidth(300)
				.MaxDesiredWidth(300)
					[
						SNew(SBorder)
						[
							DetailsView.ToSharedRef()
						]
					]
			]
			+SVerticalBox::Slot()
			.VAlign(VAlign_Bottom)
			[
				SNew(STextBlock)
				.Text(FText::FromString(TEXT("该任务序列包含的任务列表:")))
			]
			+SVerticalBox::Slot()
			.AutoHeight()
			[
				SNew(SHorizontalBox)
				+SHorizontalBox::Slot()
				.HAlign(HAlign_Fill)
				[
					SAssignNew(tasksContainer, SVerticalBox)
				]
				+SHorizontalBox::Slot()
				.HAlign(HAlign_Fill)
				[
					TaskDetailsView.ToSharedRef()					
				]
			]
		];

	RefreshTaskIcons(TaskSequence);
}

TArray<UTask*> STaskSequenceEditorSlate::GetTaskChain(UTaskSequence* taskSequence)
{
	auto LeadingTask = taskSequence->LeadingTask;
	TArray<UTask*> tasks;
	if (LeadingTask != nullptr)
	{
		tasks.Add(LeadingTask);
		UTask* currentTask = LeadingTask;
		while ((currentTask = currentTask->NextTask) != nullptr)
		{
			tasks.Add(currentTask);
		}
	}
	return tasks;
}

void STaskSequenceEditorSlate::OnLeadingTaskChanged(const FPropertyChangedEvent& event)
{
	if (event.Property->GetDisplayNameText().EqualTo(LOCTEXT("test","起始任务")))
	{
		UE_LOG(LogTemp, Warning, TEXT("%s"),*event.Property->GetDisplayNameText().ToString());

		RefreshTaskIcons(TaskSequence);
	}
	
}

void STaskSequenceEditorSlate::RefreshTaskIcons(UTaskSequence* InTaskSequence)
{
	CurrentTasks.Empty();

	if (tasksContainer.IsValid())
	{
		tasksContainer->ClearChildren();	

		//填充任务数组
		CurrentTasks = GetTaskChain(InTaskSequence);

		int32 taskCount = CurrentTasks.Num();
		for (int32 i = 0; i < taskCount; ++i)
		{
			tasksContainer->AddSlot()
				.AutoHeight()
				[
					SNew(SButton)
					.OnClicked(this, &STaskSequenceEditorSlate::OnTaskButtonClicked, i)
					.Text(FText::FromString(CurrentTasks[i]->Description))
				];
		}

		//Task的DetailsView默认显示第一个的信息
		if (CurrentTasks.Num() > 0)
		{
			TaskDetailsView->SetObject(CurrentTasks[0]);
		}
	}

}

FReply STaskSequenceEditorSlate::OnTaskButtonClicked(int32 ClickedIndex)
{
	TaskDetailsView->SetObject(CurrentTasks[ClickedIndex]);
	return FReply::Handled();
}

#undef LOCTEXT_NAMESPACE