// Fill out your copyright notice in the Description page of Project Settings.

#include "TestThread.h"

TestThread::TestThread()
{
}

TestThread::~TestThread()
{
}

uint32 TestThread::Run()
{
	UE_LOG(LogTemp, Log, TEXT("Run"));
	if (TestInterface)
	{
		TestInterface->DoWork();
	}
	return 0;
}

void TestThread::CreateThread(IRunableInterface * NewTestInterface)
{
	TestInterface = NewTestInterface;
	Test_Thread = FRunnableThread::Create(this, TEXT("HelloWorld"), 0, TPri_Normal);
}

