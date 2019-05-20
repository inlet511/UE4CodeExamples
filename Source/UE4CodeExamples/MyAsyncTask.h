#pragma once
#include "CoreMinimal.h"
#include "AsyncWork.h"

class MyAsyncTask :public FNonAbandonableTask
{
	friend class FAsyncTask<MyAsyncTask>;

	int32 InstanceInt;

	MyAsyncTask(int32 InputInt)
		:InstanceInt(InputInt)
	{

	}

	void DoWork()
	{
		UE_LOG(LogTemp, Log, TEXT("DoWorkd %d"), InstanceInt);
	}

	FORCEINLINE TStatId GetStatId() const
	{
		RETURN_QUICK_DECLARE_CYCLE_STAT(MyAsyncTask, STATGROUP_ThreadPoolAsyncTasks);
	}

};