#include "CoreMinimal.h"
#include "TaskGraphInterfaces.h"

class FTaskGraph
{
public:

	FTaskGraph(float f)
		:m_f(f)
	{

	}

	static ESubsequentsMode::Type GetSubsequentsMode()
	{
		return ESubsequentsMode::TrackSubsequents;
	}

	FORCEINLINE TStatId GetStatId()
	{
		RETURN_QUICK_DECLARE_CYCLE_STAT(FTaskGraph, STATGROUP_TaskGraphTasks);
	}

	void DoTask(ENamedThreads::Type CurrentThread, FGraphEventRef Subsequents)
	{
		UE_LOG(LogTemp, Log, TEXT("Hello World %f"), m_f);
	}

	static ENamedThreads::Type GetDesiredThread()
	{
		return ENamedThreads::AnyThread;
	}

private:
	float m_f;

};
