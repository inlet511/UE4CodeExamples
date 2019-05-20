// Fill out your copyright notice in the Description page of Project Settings.

#include "MyGameModeBase.h"
#include "GraphTask.h"
#include "AsyncWork.h"
#include "MyAsyncTask.h"

void AMyGameModeBase::BeginPlay()
{
	//多线程1 Runnable
	IRunableInterface * Interface = new IRunableInterface();
	TestThread * NewThread = new TestThread();

	NewThread->MyTestDelegate.BindUObject(this, &AMyGameModeBase::PrintFunc);

	NewThread->CreateThread(Interface);


	//多线程2 GraphTask
	TGraphTask<FTaskGraph>::CreateTask(NULL, ENamedThreads::GameThread).ConstructAndDispatchWhenReady(4.5f);


	//多线程3 AsyncTask
	FAsyncTask<MyAsyncTask> *MyTask = new FAsyncTask<MyAsyncTask>(3);

	//开始一个后台线程（通过线程池调用）
	MyTask->StartBackgroundTask();

	//游戏线程执行
	//MyTask->StartSynchronousTask();

	if (MyTask->IsDone())
	{
		UE_LOG(LogTemp, Log, TEXT("MyTask->IsDone"));
	}

	MyTask->EnsureCompletion();
	delete MyTask;
}

void AMyGameModeBase::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);

	delete NewThread;
	Interface = nullptr;
}

//主线程执行内容
void AMyGameModeBase::PrintFunc()
{
	UE_LOG(LogTemp, Log, TEXT("PrintFunc"));
}
