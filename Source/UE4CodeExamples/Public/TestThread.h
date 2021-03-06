// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "HAL/Runnable.h"
#include "HAL/RunnableThread.h"
#include "RunableInterface.h"

DECLARE_DELEGATE(FTestDelegate)

/**
 * 
 */
class UE4CODEEXAMPLES_API TestThread:public FRunnable
{
public:
	TestThread();

	~TestThread();

	FTestDelegate MyTestDelegate;

	virtual uint32 Run();

	void CreateThread(IRunableInterface * NewTestInterface);
private:
	IRunableInterface * TestInterface;
	FRunnableThread * Test_Thread;
};
